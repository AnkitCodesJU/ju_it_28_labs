/*
 * Producer-Consumer problem using fork(), System V shared memory
 * and System V semaphores.  The buffer size is entered by the user.
 *
 * Semaphore set (3 semaphores):
 *   SEM_MUTEX : mutual exclusion on the buffer, initial value 1
 *   SEM_EMPTY : number of free slots,           initial value = buffer size
 *   SEM_FULL  : number of filled slots,         initial value 0
 *
 * Child  (Producer): generates 'A'..'Z', puts them in the buffer, signals FULL.
 * Parent (Consumer): waits on FULL, removes a character, signals EMPTY.
 *
 * Compile: gcc -Wall -o producer_consumer producer_consumer.c
 * Run    : ./producer_consumer
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>

#define TOTAL_ITEMS 26     /* 'A' .. 'Z' */
#define MAX_BUFFER  1000   /* upper limit accepted from the user */

#define SEM_MUTEX 0
#define SEM_EMPTY 1
#define SEM_FULL  2
#define NUM_SEMS  3

/* Layout of the shared memory segment (buffer size decided at run time) */
typedef struct {
    int  capacity;   /* buffer size entered by the user */
    int  in;         /* next position the producer writes to */
    int  out;        /* next position the consumer reads from */
    char buffer[];   /* flexible array: 'capacity' slots */
} shared_t;

union semun {
    int              val;
    struct semid_ds *buf;
    unsigned short  *array;
};

/* wait / down / P operation */
static void sem_wait_op(int semid, int semnum)
{
    struct sembuf op = { (unsigned short)semnum, -1, 0 };
    while (semop(semid, &op, 1) == -1) {
        if (errno != EINTR) { perror("semop wait"); exit(EXIT_FAILURE); }
    }
}

/* signal / up / V operation */
static void sem_signal_op(int semid, int semnum)
{
    struct sembuf op = { (unsigned short)semnum, +1, 0 };
    while (semop(semid, &op, 1) == -1) {
        if (errno != EINTR) { perror("semop signal"); exit(EXIT_FAILURE); }
    }
}

static void producer(int semid, shared_t *shm)
{
    printf("[Producer] PID = %d, Parent PID = %d\n", getpid(), getppid());
    fflush(stdout);

    for (int i = 0; i < TOTAL_ITEMS; i++) {
        char item = 'A' + i;                  /* i.   generate next character */

        sem_wait_op(semid, SEM_EMPTY);        /* wait for a free slot */
        sem_wait_op(semid, SEM_MUTEX);        /* enter critical section */

        int pos = shm->in;
        shm->buffer[pos] = item;              /* ii.  place into shared buffer */
        shm->in = (pos + 1) % shm->capacity;

        printf("Producer: Produced %c at buffer position %d\n", item, pos); /* iii. */
        fflush(stdout);

        sem_signal_op(semid, SEM_MUTEX);      /* leave critical section */
        sem_signal_op(semid, SEM_FULL);       /* iv.  signal data available */
    }

    printf("Producer: Finished. Total characters produced = %d\n", TOTAL_ITEMS);
    fflush(stdout);
}

static void consumer(int semid, shared_t *shm, char *consumed)
{
    for (int i = 0; i < TOTAL_ITEMS; i++) {
        sem_wait_op(semid, SEM_FULL);         /* i.   wait until data is available */
        sem_wait_op(semid, SEM_MUTEX);        /* enter critical section */

        int pos = shm->out;
        char item = shm->buffer[pos];         /* ii.  read ... */
        shm->buffer[pos] = '\0';              /*      ... and remove */
        shm->out = (pos + 1) % shm->capacity;
        consumed[i] = item;

        printf("Consumer: Consumed %c from buffer position %d\n", item, pos); /* iii. */
        fflush(stdout);

        sem_signal_op(semid, SEM_MUTEX);      /* leave critical section */
        sem_signal_op(semid, SEM_EMPTY);      /* iv.  signal buffer space available */
    }
}

int main(void)
{
    setvbuf(stdout, NULL, _IOLBF, 0);

    /* ---- read buffer size from the user ---- */
    int buffer_size = 0;
    printf("Enter buffer size (1 to %d): ", MAX_BUFFER);
    fflush(stdout);
    if (scanf("%d", &buffer_size) != 1 || buffer_size < 1 || buffer_size > MAX_BUFFER) {
        fprintf(stderr, "Invalid buffer size. Please enter an integer between 1 and %d.\n",
                MAX_BUFFER);
        return EXIT_FAILURE;
    }

    /* ---- create shared memory ---- */
    size_t shm_bytes = sizeof(shared_t) + (size_t)buffer_size;
    int shmid = shmget(IPC_PRIVATE, shm_bytes, IPC_CREAT | 0600);
    if (shmid == -1) { perror("shmget"); return EXIT_FAILURE; }

    shared_t *shm = (shared_t *)shmat(shmid, NULL, 0);
    if (shm == (void *)-1) {
        perror("shmat");
        shmctl(shmid, IPC_RMID, NULL);
        return EXIT_FAILURE;
    }
    memset(shm, 0, shm_bytes);
    shm->capacity = buffer_size;

    /* ---- create and initialise semaphores ---- */
    int semid = semget(IPC_PRIVATE, NUM_SEMS, IPC_CREAT | 0600);
    if (semid == -1) {
        perror("semget");
        shmdt(shm); shmctl(shmid, IPC_RMID, NULL);
        return EXIT_FAILURE;
    }

    union semun arg;
    unsigned short init[NUM_SEMS];
    init[SEM_MUTEX] = 1;
    init[SEM_EMPTY] = (unsigned short)buffer_size;
    init[SEM_FULL]  = 0;
    arg.array = init;
    if (semctl(semid, 0, SETALL, arg) == -1) {
        perror("semctl SETALL");
        shmdt(shm); shmctl(shmid, IPC_RMID, NULL); semctl(semid, 0, IPC_RMID);
        return EXIT_FAILURE;
    }

    printf("Parent (Consumer) PID = %d\n", getpid());
    printf("Buffer capacity           : %d\n", buffer_size);
    printf("Initial semaphore values  : mutex = %d, empty = %d, full = %d\n",
           semctl(semid, SEM_MUTEX, GETVAL), semctl(semid, SEM_EMPTY, GETVAL),
           semctl(semid, SEM_FULL, GETVAL));
    printf("----------------------------------------------------------\n");
    fflush(stdout);

    /* ---- create the producer (child) ---- */
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        shmdt(shm); shmctl(shmid, IPC_RMID, NULL); semctl(semid, 0, IPC_RMID);
        return EXIT_FAILURE;
    }

    if (pid == 0) {                 /* ------- child: PRODUCER ------- */
        producer(semid, shm);
        shmdt(shm);                 /* detach only; parent removes the IPC objects */
        _exit(EXIT_SUCCESS);
    }

    /* ------- parent: CONSUMER ------- */
    printf("[Consumer] PID = %d, Child (Producer) PID = %d\n", getpid(), pid);
    fflush(stdout);

    char consumed[TOTAL_ITEMS + 1];
    memset(consumed, 0, sizeof(consumed));
    consumer(semid, shm, consumed);

    /* ---- wait for child to terminate ---- */
    int status;
    pid_t done = waitpid(pid, &status, 0);

    printf("----------------------------------------------------------\n");
    printf("Total characters produced : %d\n", TOTAL_ITEMS);
    printf("Total characters consumed : %d\n", TOTAL_ITEMS);

    /* ---- verify the consumed sequence ---- */
    char expected[TOTAL_ITEMS + 1];
    for (int i = 0; i < TOTAL_ITEMS; i++) expected[i] = 'A' + i;
    expected[TOTAL_ITEMS] = '\0';

    printf("Consumed sequence         : %s\n", consumed);
    printf("Verification              : %s\n",
           strcmp(consumed, expected) == 0
               ? "SUCCESS - consumed sequence is exactly A through Z"
               : "FAILURE - consumed sequence does not match A..Z");

    if (done == pid && WIFEXITED(status))
        printf("Child process %d terminated with exit status %d\n",
               (int)pid, WEXITSTATUS(status));
    else
        printf("Child process %d did not terminate normally\n", (int)pid);

    /* ---- release IPC resources ---- */
    int ok = 1;
    if (shmdt(shm) == -1)                    { perror("shmdt");  ok = 0; }
    if (shmctl(shmid, IPC_RMID, NULL) == -1) { perror("shmctl"); ok = 0; }
    if (semctl(semid, 0, IPC_RMID) == -1)    { perror("semctl"); ok = 0; }

    printf("Shared memory and semaphores %s\n",
           ok ? "have been released (removed)" : "could NOT be fully released");

    return ok ? EXIT_SUCCESS : EXIT_FAILURE;
}
