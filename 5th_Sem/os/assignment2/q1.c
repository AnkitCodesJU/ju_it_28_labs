#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } 
    else if (pid == 0) {
        printf("Child Processing\n");
        printf("I am child and my process id is %d\n", getpid());
        printf("I am child and my parents process id is %d\n", getppid());
    } 
    else {
        wait(NULL); 
        
        printf("Parent processing\n");
        printf("I am parent and my process id is %d\n", getpid());
        printf("I am parent and my parents process id is %d\n", getppid());
    }

    return 0;
}
