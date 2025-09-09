#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1 = fork();
    pid_t pid2 = fork();
    
    if (pid1 == 0 && pid2 > 0) {
        // First child process (created by first fork, parent in second fork)
        printf("Child 1, PID: %d\n", getpid());
    } else if (pid1 > 0 && pid2 == 0) {
        // Second child process (parent in first fork, created by second fork)
        printf("Child 2, PID: %d\n", getpid());
    } else if (pid1 > 0 && pid2 > 0) {
        // Parent process
        printf("I am the parent, PID: %d\n", getpid());
        // Wait for both children
        wait(NULL);
        wait(NULL);
    } else {
        // This would be a grandchild process (child of child)
        // We'll just exit to avoid confusion
        return 0;
    }
    
    return 0;
}
