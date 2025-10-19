#include "global_pipe.h"
#include "utils.h"
#include<unistd.h>

void get_password() {
    // Uses applescript to prompts the user to write 
    // a password and writes it into the pipe
    good_sound;

    int fd_pass[2] = {0};
    if (pipe(fd_pass) == -1) {
        printf("ERROR\n");
    }

    pid_t pid = fork();
    if (pid == 0) {
        dup2(fd_pass[1], 1);
        close(fd_pass[0]);
        close(fd_pass[1]);
        execlp(
            "osascript",
            "osascript",
            "./EyeCript/utils/apple_scripts/choosePassword.applescript",
            NULL
        );
    } else if (pid < 0) {
        exit(1);
    }
    close(fd_pass[1]);

    wait(NULL);

    // Remove newline save data
    init_pipe();
    pid = fork();
    if (pid == 0) {
        dup2(fd_pass[0], 0);
        close(fd_pass[0]);
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        execlp(
            "cat",
            "cat",
            NULL
        );
    } else if (pid < 0) {
        exit(1);
    }
    close(fd_pass[0]);
    close(fd[1]);

    wait(NULL);

    char password[100];
    read(fd[0], password, 99);
    for (int i = 0; i < strlen(password); i++) {
        printf("%c", password[i]);
    }
    printf("a");
    printf("a\nDONE\n");
    return;
}