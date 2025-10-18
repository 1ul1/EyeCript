#include "utils.h"

#include <stdio.h>
#include <string.h>

char* get_extension(const char* filename) {
    // Get extension of file
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        bad_sound;
        visual_error;

        exit(6);
        return NULL;
    }

    fseek(file, -1, SEEK_END);
    int len = (int)fgetc(file);
    fseek(file, -len - 1, SEEK_CUR);
    char* extension = malloc (sizeof(char) * (len + 1));
    fread(extension, sizeof(char), len, file);

    *(extension + len) = '\0';

    int truncate_size = ftell(file);

    fclose(file);
    // remove footer
    if (truncate(filename, truncate_size) == -1) {
        bad_sound;
        visual_error;

        exit(6);
        return NULL;
    }

    return extension;
}