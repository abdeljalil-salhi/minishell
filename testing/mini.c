#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LINE_LENGTH 256

int main(void) {
    char line[MAX_LINE_LENGTH];
    char *args[MAX_LINE_LENGTH / 2 + 1];
    int status;

    while (1) {
        printf("minishell> ");
        fgets(line, MAX_LINE_LENGTH, stdin);
        line[strcspn(line, "\n")] = 0;

        int i = 0;
        char *token = strtok(line, " ");
        while (token != NULL) {
            args[i] = token;
            i++;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        pid_t pid = fork();
        if (pid == 0) {
            execvp(args[0], args);
            printf("Error: command not found\n");
            exit(EXIT_FAILURE);
        } else if (pid > 0) {
            wait(&status);
        } else {
            printf("Error: fork failed\n");
            exit(EXIT_FAILURE);
        }
    }
    return (0);
}
