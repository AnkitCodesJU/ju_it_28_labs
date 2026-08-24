#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    printf("\n--- 1. execl demonstrating 'pwd' ---\n");
    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        execl("/bin/pwd", "pwd", (char *)NULL);
        perror("execl failed");
        exit(1);
    } else {
        wait(NULL);
    }

    printf("\n--- 2. execv demonstrating 'whoami' ---\n");
    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        char *args[] = {"whoami", NULL};
        execv("/usr/bin/whoami", args);
        perror("execv failed");
        exit(1);
    } else {
        wait(NULL);
    }

    printf("\n--- 3. execlp demonstrating 'ls' ---\n");
    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        execlp("ls", "ls", (char *)NULL);
        perror("execlp failed");
        exit(1);
    } else {
        wait(NULL);
    }

    printf("\n--- 4. execvp demonstrating 'ls -l' ---\n");
    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        char *args[] = {"ls", "-l", NULL};
        execvp("ls", args);
        perror("execvp failed");
        exit(1);
    } else {
        wait(NULL);
    }

    printf("\nAll exec calls completed successfully.\n");
    return 0;
}
