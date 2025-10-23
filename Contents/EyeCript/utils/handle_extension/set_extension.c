#include "utils.h"

#include <stdio.h>
#include <string.h>

void set_extension(const char* filename, const char* extension) {
    // Add extension in footer
    FILE* file = fopen(filename, "rb+");
    if (file == NULL) {
        bad_sound;
        visual_error;

        perror("File does not exist");
        exit(7);
        return;
    }

    fseek(file, 0, SEEK_END);

    fputs(extension, file);
    fputc((char)strlen(extension), file);

    fclose(file);

    return;
}