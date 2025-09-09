#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    char command[256];
    
    while (1) {
        printf("myshell> ");
        fgets(command, sizeof(command), stdin);
        
        // Remove newline character
        command[strcspn(command, "\n")] = 0;
        
        // Check for exit command
        if (strcmp(command, "exit") == 0) {
            printf("Goodbye!\n");
            break;
        }
        
        // Skip empty commands
        if (strlen(command) == 0) {
            continue;
        }
        
        pid_t pid = fork();
        
        if (pid == 0) {
            // Child process - execute the command
            // Parse the command into arguments
            char *args[64];
            char *token = strtok(command, " ");
            int i = 0;
            
            while (token != NULL && i < 63) {
                args[i] = token;
                token = strtok(NULL, " ");
                i++;
            }
            args[i] = NULL;
            
            // Execute the command
            execvp(args[0], args);
            
            // If execvp fails
            printf("Command execution failed!\n");
            exit(1);
        } else if (pid > 0) {
            // Parent process - wait for child to finish
            wait(NULL);
        } else {
            printf("Fork failed!\n");
        }
    }
    
    return 0;
}
