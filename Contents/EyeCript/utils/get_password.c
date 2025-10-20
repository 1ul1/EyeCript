#include "global_pipe.h"
#include "utils.h"
#include<unistd.h>

void get_password() {
    // Uses applescript to prompts the user to write 
    // a password and writes it into the pipe
    good_sound;

    int fd_pass[2] = {0};
    if (pipe(fd_pass) == -1) {
        bad_sound;
        visual_error;
        exit(8);
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
        bad_sound;
        visual_error;
        exit(8);
    } else if (pid < 0) {
        bad_sound;
        visual_error;
        exit(8);
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
        if (fd[0] > 2) // To not close stdin
            close(fd[0]);
        close(fd[1]);
        execlp(
            "tr",
            "tr",
            "-d",
            "\n",
            NULL
        );
        bad_sound;
        visual_error;
        exit(8);
    } else if (pid < 0) {
        bad_sound;
        visual_error;
        exit(8);
    }
    close(fd[1]);

    wait(NULL);

    close(fd_pass[0]);

    return;
}