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

#define COUNTDOWN       15
#define DECIMAL_BASE    10
#define ANSWER_TO_EVERYTHING 42
#define FORKED_LOTS     12

typedef struct {
    int countdown;
    bool forkbomb;
    int forkcount;
    int correctguess;
} SecretSettings;

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

SecretSettings parse_secrets(int argc, char *argv[]) {
    SecretSettings params = {
        .countdown = 15, .forkbomb = false, .forkcount = 2, .correctguess = 4
    };
    int opt;
    /* Blame user if arguments are cooked */
    while ((opt = getopt(argc, argv, "c:bf:g")) != -1) {
        switch (opt) {
        case 'c':
            params.countdown = atoi(optarg);
            break;
        case 'b':
            params.forkbomb = true; /* Uh oh, forkbomb activated */
            break;
        case 'f':
            params.forkcount = atoi(optarg);
            break;
        case 'g':
            params.correctguess = atoi(optarg);
            break;
        default:
            fprintf(stderr, "Usage: %s [-c loops] [-b] [-f forks]\n",
                    argv[0]);
            exit(1);
        }
    }
    return params;
}

int main(int argc, char *argv[]) {
    SecretSettings params = parse_secrets(argc, argv);
    char *line = NULL;
    size_t length = 0;
    char *endptr;
    int guess;
    int errno = 0;

    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = interrupt;
    sigaction(SIGINT, &sa, 0);
    sigaction(SIGQUIT, &sa, 0);
    sigaction(SIGTSTP, &sa, 0);

    int countdown = (params.countdown == 0) ? COUNTDOWN : params.countdown;
    while (true)
    {
        sleep(1.5);
        printf("Haiii :3\n");
        printf("Fork bombing your device in %d!!!\n", countdown);
        if (countdown == 0) {
            printf("Time to meet your demise... play a game or else hehehe\n");
            break;
        }
        countdown -= 1;
    }

    printf("Guess a number between 1 and 6!\n");
    if (getline(&line, &length, stdin) == EOF) {
        printf("Hmm... no guess... straight to the blender >:3\n");
        goto forkbomb;
    }
    guess = strtol(line, &endptr, DECIMAL_BASE);
    if (errno) {
        printf("Wrong format... bombing\n");
        goto forkbomb;
    }
    if (endptr == line) {
        printf("Hmm... no digits found\n");
        goto forkbomb;
    }
    if (guess != params.correctguess) {
        printf("Wrong number hehehe\n");
        goto forkbomb;
    } else {
        printf("You guessed right... :(\n");
        return (0);
    }

forkbomb:
    if (params.forkbomb) {
        printf("Uh oh, infinite forkbomb activated...\n");
        printf("Current Version doesn't support forkbomb for testing safety\n");
        // while (true)
        // {
        //     fork();
        // }
        return (ANSWER_TO_EVERYTHING);
    }
    for (int i = 0; i < 1; i++) {
        if (fork()) {
            printf("Fork %d in parent\n", i);
        } else {
            printf("Fork %d in child\n", i);
        }
    }
    
    return (FORKED_LOTS);
}
