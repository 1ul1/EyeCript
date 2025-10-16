#ifndef UTILS_H
#define UTILS_H

#include "global_pipe.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define good_sound system("afplay /System/Library/Sounds/Glass.aiff &")
#define bad_sound system("afplay /System/Library/Sounds/Sosumi.aiff &")
#define visual_error system("osascript ./EyeCript/utils/apple_scripts/error.applescript")

void get_new_file();

void get_file();

void get_password();

void set_extension(const char* filename, const char* extension);
char* find_extension(const char* filename);
char* get_extension(const char* filename);

#endif