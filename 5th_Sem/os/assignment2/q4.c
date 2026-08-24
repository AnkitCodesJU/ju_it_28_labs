#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>

void benchmark_syscalls() {
    struct timeval start, end;
    double getpid_total_time, fork_total_time;
    int i;

    printf("\n--- Task (vi) & (vii): Measure system calls ---\n");
    
    gettimeofday(&start, NULL);
    for (i = 0; i < 10; i++) getpid();
    gettimeofday(&end, NULL);
    getpid_total_time = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);
    
    gettimeofday(&start, NULL);
    for (i = 0; i < 10; i++) {
        if (fork() == 0) exit(0);
        else wait(NULL);
    }
    gettimeofday(&end, NULL);
    fork_total_time = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);

    printf("Average getpid() execution time: %.3f microseconds\n", getpid_total_time / 10.0);
    printf("Average fork() execution time: %.3f microseconds\n", fork_total_time / 10.0);
}

int main() {
    pid_t pid;

    printf("******************************************************************\n");
    printf("* DISCLAIMER: Do not kill the process.. it will take time due to *\n");
    printf("* sleep() calls! It will run for roughly 50-60 seconds total.    *\n");
    printf("******************************************************************\n");

    printf("\n--- Task (i) & (ii): NO SYNC, Both sleep(1) ---\n");
    pid = fork();
    if (pid == 0) {
        printf("child process\n");
        printf("Child ID: %d, Parent ID: %d\n\n", getpid(), getppid());
        for (int i = 1; i <= 19; i += 2) {
            printf("%d ", i); fflush(stdout);
            sleep(1);
        }
        exit(0);
    } else {
        printf("In parent process\n");
        printf("Parent ID: %d, Grandparent ID: %d\n", getpid(), getppid());
        for (int i = 2; i <= 20; i += 2) {
            printf("%d ", i); fflush(stdout);
            sleep(1);
        }
        wait(NULL); 
        printf("\n[Notice how the numbers are mixed up because there is no sync]\n");
    }

    printf("\n--- Task (iii): NO SYNC, Child sleep(2), Parent sleep(1) ---\n");
    pid = fork();
    if (pid == 0) {
        for (int i = 1; i <= 19; i += 2) {
            printf("%d ", i); fflush(stdout);
            sleep(2); 
        }
        exit(0);
    } else {
        for (int i = 2; i <= 20; i += 2) {
            printf("%d ", i); fflush(stdout);
            sleep(1); 
        }
        wait(NULL);
        printf("\n[What happens? The parent finishes evens way faster. The child is left printing odds slowly at the end.]\n");
    }

    printf("\n--- Task (iv): SYNCHRONIZED continuous 1-20 (With sleep) ---\n");
    int p1[2], p2[2];
    pipe(p1); 
    pipe(p2); 
    
    pid = fork();
    if (pid == 0) {
        char dummy;
        for (int i = 1; i <= 19; i += 2) {
            printf("%d ", i); fflush(stdout);
            sleep(1); 
            write(p1[1], "x", 1); 
            if (i < 19) {
                read(p2[0], &dummy, 1); 
            }
        }
        exit(0);
    } else {
        char dummy;
        for (int i = 2; i <= 20; i += 2) {
            read(p1[0], &dummy, 1); 
            printf("%d ", i); fflush(stdout);
            sleep(1); 
            if (i < 20) {
                write(p2[1], "x", 1); 
            }
        }
        wait(NULL); 
        printf("\n[Perfect continuous 1-20 using pipe synchronization!]\n");
    }

    printf("\n--- Task (v): Process table (ps) ---\n");
    pid = fork();
    if (pid == 0) {
        sleep(2); 
        exit(0);
    } else {
        system("ps -al");
        wait(NULL);
    }

    benchmark_syscalls();

    return 0;
}
