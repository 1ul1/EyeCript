#include "global_pipe.h"
#include "utils.h"
#include<unistd.h>

void get_new_file() {
    // Uses applescript to prompts the user to select 
    // a file and writes it into the pipe
    good_sound;

    int fd_error[2] = {0};
    if (pipe(fd_error) == -1) {
        bad_sound;
        visual_error;
        exit(8);
    }

    pid_t pid = fork();

    if (pid == 0) {
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        dup2(fd_error[1], 2);
        close(fd_error[0]);
        close(fd_error[1]);
        execlp(
            "osascript",
            "osascript",
            "./EyeCript/utils/apple_scripts/chooseWhereToSave.applescript",
            NULL
        );
        exit(1);
    } else if (pid < 0) {
        exit(1);
    }
    close(fd_error[1]);

    wait(NULL);

    char error[1];
    if (read(fd_error[0], error, sizeof(char)) > 0) {
        perror("User canceled applescript");
        exit(0);
    }

    return;
}