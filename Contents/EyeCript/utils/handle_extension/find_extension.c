#include "utils.h"

#include <string.h>
#include <stdlib.h>

char* find_extension(const char* filename) {
    // Get extension of file
    const char* pos = strrchr(filename, '.');
    if (pos == NULL)
        return NULL;
    else if (*(pos + 1) == '\0')
        return NULL;

    int len = strlen(pos + 1);
    if (len >= 16) {
        bad_sound;
        visual_error;

        exit(5);
        return;
    }

    char* extension = malloc(sizeof(char) * (len + 1));
    memcpy(extension, pos + 1, len);
    *(extension + len) = '\0';
    return extension;
}