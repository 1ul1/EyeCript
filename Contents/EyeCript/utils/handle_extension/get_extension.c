#include "utils.h"

#include <stdio.h>
#include <string.h>

char* get_extension(const char* filename) {
    // Get extension of file
    // And remove footer if needed
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        bad_sound;
        visual_error;

        perror("File does not exist");
        exit(6);
        return NULL;
    }

    if (fseek(file, -1, SEEK_END) != 0) {
        bad_sound;
        visual_error;

        perror("Fseek failed");
        exit(6);
    }
    int len = (int)fgetc(file);
    fseek(file, -len -1, SEEK_CUR);
    char* extension = malloc (sizeof(char) * (len + 1));
    fread(extension, sizeof(char), len, file);

    *(extension + len) = '\0';
    
    int truncate_size = ftell(file) - len;

    fclose(file);
    // remove footer
    if (truncate(filename, truncate_size) == -1) {
        bad_sound;
        visual_error;

        perror("Truncate failed");
        exit(6);
        return NULL;
    }

    return extension;
}