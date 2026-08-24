#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    printf("--- ZOMBIE PROCESS DEMONSTRATION ---\n");
    pid_t pid1 = fork();

    if (pid1 < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } 
    else if (pid1 > 0) {
        sleep(1); 
        
        printf("Parent process ID: %d\n", getpid());
        printf("Parent's PPID: %d\n", getppid());
        printf("Child process ID (Zombie): %d\n", pid1);
        printf("\nExecuting: ps -l | grep Z\n");
        
        system("ps -l | grep Z");
        
        wait(NULL); 
        
        printf("\n--- ORPHAN PROCESS DEMONSTRATION ---\n");
        
        pid_t main_pid = fork();
        
        if (main_pid < 0) {
            fprintf(stderr, "Fork failed\n");
            return 1;
        }
        else if (main_pid > 0) {
            wait(NULL); 
            sleep(4); 
        }
        else if (main_pid == 0) {
            pid_t pid2 = fork();
            
            if (pid2 > 0) {
                printf("Parent process ppid: %d\n", getppid());
                sleep(1); 
                exit(0); 
            } 
            else if (pid2 == 0) {
                printf("Before Orphan -> Child PID: %d, Parent PID: %d\n", getpid(), getppid());
                
                sleep(3); 
                
                printf("After Orphan -> Child PID: %d, Parent is init process whose id is %d\n", getpid(), getppid());
                exit(0);
            }
        }
    } 
    else if (pid1 == 0) {
        exit(0);
    }

    return 0;
}
