#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
    int pipeFD[2];
    pid_t pid;
    char message[] = "Hy";

    if (pipe(pipeFD) == -1) {
        perror("Failed to create pipe!");
        return 1;
    }

    pid = fork();

    if (pid == -1) {
        perror("Error creating the process!");
        return 1;
    }

    if (pid == 0) {
        close(pipeFD[0]);
        write(pipeFD[1], message, strlen(message) + 1);
        close(pipeFD[1]);
        return 0;
    } else {
        close(pipeFD[1]);
        char received_message[strlen(message) + 1];
        read(pipeFD[0], received_message, sizeof(received_message));
        printf("Received message: %s\n", received_message);
        close(pipeFD[0]);
        return 0;
    }
}
