#include "global_pipe.h"
#include <unistd.h>
#include <stdlib.h>

int fd[2] = {0};

void init_pipe() {
    if (pipe(fd) != 0)
        exit(2);
}
