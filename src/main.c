#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

char *exec(char *line) {
    char *token, *Token[64];
    int i = 0;
    token = strtok(line, " ");
    do {
        Token[i] = token;
        i++;
    } while ((token = strtok(NULL, " ")));

    Token[i] = NULL;

    pid_t child = fork();

    if (child == -1) {
        perror("fork");
        return NULL;
    }

    char *command = Token[0];

    if (child == 0) {
        int status_code = execvp(command, Token);

        perror("execvp");

        return NULL;
    } else {
        waitpid(child, NULL, 0);
    }

    return *Token;
}

int main() {

    char line[1024];
    printf("Welcome to Oh-my-gosh");

    while (1) {

        printf(">$ ");
        fgets(line, 1024, stdin);

        line[strlen(line) - 1] = '\0';

        if (!strcmp(line, "exit")) {
            exit(0);
        }

        exec(line);
    }
}
