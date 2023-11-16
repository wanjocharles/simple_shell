#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(void) {
    char buffer[BUFFER_SIZE];
    char *cmd;

    while (1) {
        printf("#cisfun$ ");
        fflush(stdout);

        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            printf("\n");
            break; // Exit on EOF (Ctrl+D)
        }

        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character

        cmd = strtok(buffer, " "); // Tokenize the command

        if (cmd == NULL) {
            continue; // Empty input, prompt again
        }

        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            if (execlp(cmd, cmd, (char *)NULL) == -1) {
                printf("./shell: No such file or directory\n");
                exit(EXIT_FAILURE);
            }
        } else {
            int status;
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}

