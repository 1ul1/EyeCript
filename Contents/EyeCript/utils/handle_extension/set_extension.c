#include "utils.h"

#include <stdio.h>
#include <string.h>

void set_extension(const char* filename, const char* extension) {
    // Add extension in footer
    FILE* file = fopen(filename, "ab");
    if (file == NULL) {
        bad_sound;
        visual_error;

        exit(5);
        return;
    }

    fputs(extension, file);
    fputc((char)strlen(extension), file);

    fclose(file);

    return;
}