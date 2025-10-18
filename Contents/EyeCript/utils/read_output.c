#include "utils.h"

void read_output(char* line) {
    // Read one full line from pipe
    int i = 0;
    do {
        read(fd[0], line + i, sizeof(char));
        i = i + 1;
    } while (line[i - 1] != '\n');
    line[i - 1] = '\0';

    return;
}