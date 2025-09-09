#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child process
        printf("Executing ls command...\n");
        execlp("ls", "ls", "-l", NULL);
        // If execlp fails, we'll reach this point
        printf("Command execution failed!\n");
        return 1;
    } else if (pid > 0) {
        // Parent process
        wait(NULL);
        printf("Parent process finished.\n");
    } else {
        printf("Fork failed!\n");
        return 1;
    }
    
    return 0;
}
