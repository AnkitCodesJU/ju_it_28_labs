/***********************************************************************
*
* Name- Ankit Roy, Roll- 002411001028
* Name- Saptarshi Sau, Roll- 002411001031
* Team-Number-05, Section- A1
* Assignment Number: 7
* Date: 6th November 2026

* Output Description:
*       - The PID of the parent (Consumer) and of the child (Producer),
*         using getpid() and getppid().
*       - The buffer capacity and the initial values of the semaphores
*         (empty = buffer size, full = 0). No mutex is used.
*       - One line for every production event and every consumption event,
*         with the character and its buffer position, e.g.
*             Producer: Produced A at buffer position 0
*             Consumer: Consumed A from buffer position 0
*       - The total number of characters produced and consumed (26 each).
*       - A verification that the consumed sequence is exactly A..Z.
*       - A PROOF section: runtime checks showing that the child process
*         has terminated and that the shared memory and the semaphores
*         have been removed, followed by a final YES / NO confirmation.
*
* Compilation command: gcc -Wall -o A1_05_ASN-7 A1_05_ASN-7.c
*       -Wall     : enable all common compiler warnings
*       (no -lpthread needed: this program uses fork() and System V IPC,
*        not threads)
*
* Execution sequence:
*       ./A1_05_ASN-7
*       Enter buffer size (1 to 1000): 5
*
* Assignment Details:
*       Producer-Consumer problem with two PROCESSES that share a
*       fixed-size circular buffer. The producer (child) generates the
*       characters 'A' to 'Z' and the consumer (parent) removes them one
*       at a time. Synchronisation uses a System V semaphore set:
*           empty : counting semaphore, initial value = buffer size
*                   -> number of free slots (producer waits when 0)
*           full  : counting semaphore, initial value 0
*                   -> number of filled slots (consumer waits when 0)
*       NO mutex is needed: there is exactly ONE producer and ONE
*       consumer, the producer only changes 'in' and the consumer only
*       changes 'out', and empty/full guarantee that they never touch the
*       same slot at the same time.
*
* Walk-through (order of execution):
*       1. main() reads the buffer size from the user and validates it.
*       2. main() creates the shared memory segment (shmget/shmat) and the
*          semaphore set (semget), and initialises them (semctl SETALL).
*       3. main() prints the parent PID, buffer capacity and initial
*          semaphore values, then calls fork().
*       4. CHILD = PRODUCER, repeated for 'A'..'Z':
*              wait(empty)   : block if the buffer is full
*              store the character at buffer[in]; in = (in+1) % size;
*              print "Produced <ch> at buffer position <pos>"
*              signal(full)  : tell the consumer that data is available
*          then the child detaches from the shared memory and exits.
*       5. PARENT = CONSUMER, repeated 26 times:
*              wait(full)    : block if the buffer is empty
*              read and remove buffer[out]; out = (out+1) % size;
*              print "Consumed <ch> from buffer position <pos>"
*              signal(empty) : tell the producer that space is available
*       6. The parent calls waitpid() to wait for the child to terminate,
*          prints the totals and checks that the consumed string is
*          exactly "ABCDEFGHIJKLMNOPQRSTUVWXYZ".
*       7. The parent detaches and removes the shared memory and the
*          semaphores (IPC_RMID), then re-checks with the kernel that the
*          child process and all IPC resources are really gone.
*
* Why this is correct:
*       - wait()/signal() are single semop() system calls, so each one is
*         atomic (done inside the kernel).
*       - With one producer and one consumer, empty and full alone give
*         mutual exclusion on every slot: the consumer can read a slot only
*         after the producer has signalled full for it, and the producer
*         can overwrite a slot only after the consumer has signalled empty
*         for it. 'in' is written only by the producer and 'out' only by
*         the consumer, so they never race.
*       - signal() is a system call (a full memory barrier), so the data
*         written to the slot is visible to the other process before it
*         wakes up.
*       - With MORE than one producer or consumer a mutex WOULD be needed
*         to protect 'in' / 'out'.
*
* Input Description: Interactive, read from the keyboard (stdin).
*       Buffer size = integer from 1 to 1000. Anything else (a letter, 0,
*       a negative number or a value above 1000) is rejected with an
*       error message and the program exits before creating any IPC
*       resource. A size smaller than 26 makes the buffer positions wrap
*       around and makes the producer wait when the buffer is full.
*
*
* NOTE: Needs Linux / WSL (System V IPC and fork() are not available in
*       plain Windows compilers).
*
*
***********************************************************************/


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
#include <signal.h>

#define TOTAL_ITEMS 26     /* 'A' .. 'Z' */
#define MAX_BUFFER  1000   /* upper limit accepted from the user */

#define SEM_EMPTY 0
#define SEM_FULL  1
#define NUM_SEMS  2

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

        int pos = shm->in;
        shm->buffer[pos] = item;              /* ii.  place into shared buffer */
        shm->in = (pos + 1) % shm->capacity;

        printf("Producer: Produced %c at buffer position %d\n", item, pos); /* iii. */
        fflush(stdout);

        sem_signal_op(semid, SEM_FULL);       /* iv.  signal data available */
    }

    printf("Producer: Finished. Total characters produced = %d\n", TOTAL_ITEMS);
    fflush(stdout);
}

static void consumer(int semid, shared_t *shm, char *consumed)
{
    for (int i = 0; i < TOTAL_ITEMS; i++) {
        sem_wait_op(semid, SEM_FULL);         /* i.   wait until data is available */

        int pos = shm->out;
        char item = shm->buffer[pos];         /* ii.  read ... */
        shm->buffer[pos] = '\0';              /*      ... and remove */
        shm->out = (pos + 1) % shm->capacity;
        consumed[i] = item;

        printf("Consumer: Consumed %c from buffer position %d\n", item, pos); /* iii. */
        fflush(stdout);

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
    printf("Initial semaphore values  : empty = %d, full = %d\n",
           semctl(semid, SEM_EMPTY, GETVAL), semctl(semid, SEM_FULL, GETVAL));
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

    /* ---- PROOF 1: child has terminated ---- */
    printf("----------------------- PROOF -----------------------\n");
    if (done == pid && WIFEXITED(status))
        printf("[Proof 1a] waitpid() reaped child %d, exit status = %d\n",
               (int)pid, WEXITSTATUS(status));
    else
        printf("[Proof 1a] Child %d did NOT terminate normally\n", (int)pid);

    /* the child must have detached from the shared memory before exiting */
    struct shmid_ds ds;
    if (shmctl(shmid, IPC_STAT, &ds) == 0)
        printf("[Proof 1b] Processes attached to shared memory = %lu "
               "(1 means only the parent; the child has detached)\n",
               (unsigned long)ds.shm_nattch);

    /* ---- release IPC resources ---- */
    int ok = 1;
    if (shmdt(shm) == -1)                    { perror("shmdt");  ok = 0; }
    if (shmctl(shmid, IPC_RMID, NULL) == -1) { perror("shmctl"); ok = 0; }
    if (semctl(semid, 0, IPC_RMID) == -1)    { perror("semctl"); ok = 0; }

    /* ---- PROOF 2: re-check with the kernel that everything is really gone ---- */

    /* (a) the child PID no longer exists: kill(pid, 0) sends no signal,
     *     it only tests whether the process exists */
    errno = 0;
    int child_gone = (kill(pid, 0) == -1 && errno == ESRCH);
    printf("[Proof 2a] kill(%d, 0) -> %s : child process %s\n", (int)pid,
           child_gone ? "ESRCH (no such process)" : "still exists",
           child_gone ? "no longer exists" : "STILL EXISTS");

    /* (b) no child is left to wait for (no zombie) */
    errno = 0;
    int no_zombie = (waitpid(pid, NULL, WNOHANG) == -1 && errno == ECHILD);
    printf("[Proof 2b] waitpid(%d) again -> %s : %s\n", (int)pid,
           no_zombie ? "ECHILD" : "unexpected result",
           no_zombie ? "no zombie / no unreaped child" : "child still unreaped");

    /* (c) the shared memory segment no longer exists */
    errno = 0;
    int shm_gone = (shmctl(shmid, IPC_STAT, &ds) == -1 &&
                    (errno == EINVAL || errno == EIDRM));
    printf("[Proof 2c] shmctl(IPC_STAT) on id %d -> %s : shared memory %s\n",
           shmid, shm_gone ? "EINVAL/EIDRM" : "succeeded",
           shm_gone ? "has been removed" : "STILL EXISTS");

    /* (d) the semaphore set no longer exists */
    errno = 0;
    int sem_gone = (semctl(semid, SEM_EMPTY, GETVAL) == -1 &&
                    (errno == EINVAL || errno == EIDRM));
    printf("[Proof 2d] semctl(GETVAL) on id %d -> %s : semaphores %s\n",
           semid, sem_gone ? "EINVAL/EIDRM" : "succeeded",
           sem_gone ? "have been removed" : "STILL EXIST");

    printf("-----------------------------------------------------\n");
    int all_ok = ok && child_gone && no_zombie && shm_gone && sem_gone;
    printf("Confirmation: child process terminated and shared resources released : %s\n",
           all_ok ? "YES (verified)" : "NO (see messages above)");

    return all_ok ? EXIT_SUCCESS : EXIT_FAILURE;
}
