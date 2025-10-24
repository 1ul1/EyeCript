#include "global_pipe.h"
#include "utils.h"
#include<unistd.h>

int get_password() {
    // Uses applescript to prompts the user to write 
    // a password and writes it into the pipe
    good_sound;

    int fd_pass[2] = {0};
    if (pipe(fd_pass) == -1) {
        bad_sound;
        visual_error;
        exit(8);
    }

    int fd_error[2] = {0};
    if (pipe(fd_error) == -1) {
        bad_sound;
        visual_error;
        exit(8);
    }

    pid_t pid = fork();
    if (pid == 0) {
        dup2(fd_pass[1], 1);
        close(fd_pass[0]);
        close(fd_pass[1]);
        dup2(fd_error[1], 2);
        close(fd_error[0]);
        close(fd_error[1]);
        execlp(
            "osascript",
            "osascript",
            "./EyeCript/utils/apple_scripts/choosePassword.applescript",
            NULL
        );
        bad_sound;
        visual_error;
        perror("Applescript failed");
        exit(8);
    } else if (pid < 0) {
        bad_sound;
        visual_error;
        exit(8);
    }
    close(fd_pass[1]);
    close(fd_error[1]);

    wait(NULL);

    char error[1];
    if (read(fd_error[0], error, sizeof(char)) > 0) {
        perror("User canceled applescript");
        return 8;
    }

    close(fd_error[0]);

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

    return 0;
}