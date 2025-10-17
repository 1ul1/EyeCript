#include "global_pipe.h"
#include "utils.h"
#include <unistd.h>
#include <stdlib.h>

int fd[2] = {0};

void init_pipe() {
    close(fd[0]);
    close(fd[1]);
    
    if (pipe(fd) != 0) {
        bad_sound;
        visual_error;
        exit(2);
    }
}
