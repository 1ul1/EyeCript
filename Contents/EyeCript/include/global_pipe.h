#ifndef GLOBAL_PIPE
#define GLOBAL_PIPE

#include<unistd.h>
#include<stdlib.h>

extern int fd[2];
void init_pipe();

#endif