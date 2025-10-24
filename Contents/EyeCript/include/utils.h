#ifndef UTILS_H
#define UTILS_H

#include "global_pipe.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define good_sound system("afplay /System/Library/Sounds/Glass.aiff &")
#define bad_sound system("afplay /System/Library/Sounds/Sosumi.aiff &")
#define success_sound system("afplay /System/Library/Sounds/Submarine.aiff &")
#define visual_error system("osascript ./EyeCript/utils/apple_scripts/error.applescript")
#define visual_wrong_pass system("osascript ./EyeCript/utils/apple_scripts/error_wrong_password.applescript")
#define visual_success system("osascript ./EyeCript/utils/apple_scripts/success.applescript")

void get_new_file();

void get_file();

int get_password();

void read_output(char* line);

char* get_extension(const char* filename);
char* find_extension(const char* filename);
void set_extension(const char* filename, const char* extension);

void encryption();
void decryption();
void preview();

extern int toggle;
void switch_toggle();

#endif