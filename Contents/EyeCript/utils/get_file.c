#include "global_pipe.h"
#include "utils.h"
#include<unistd.h>

void get_file() {
    // Uses applescript to prompts the user to select 
    // a file and writes it into the pipe
    good_sound;

    pid_t pid = fork();

    if (pid == 0) {
        dup2(fd[1], 1);
        execlp(
            "osascript",
            "osascript",
            "./EyeCript/utils/apple_scripts/selectFile.applescript",
            NULL
        );
    } else if (pid < 0) {
        exit(1);
    }
}