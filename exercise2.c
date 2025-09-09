#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1 = fork();
    
    if (pid1 > 0) {
        // Parent process
        printf("I am the parent, PID: %d\n", getpid());
        wait(NULL); // Wait for child to complete
    } else if (pid1 == 0) {
        // Child process
        printf("I am the child, PID: %d\n", getpid());
        
        pid_t pid2 = fork();
        if (pid2 == 0) {
            // Grandchild process
            printf("I am the grandchild, PID: %d\n", getpid());
        } else if (pid2 > 0) {
            // Child waits for grandchild
            wait(NULL);
        } else {
            printf("Second fork failed!\n");
        }
    } else {
        printf("First fork failed!\n");
    }
    
    return 0;
}
