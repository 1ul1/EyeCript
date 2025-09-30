#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

char* get_password() {
    // Uses applescript to prompts the user to select 
    // a file and returns the full absolute path
    system("afplay /System/Library/Sounds/Glass.aiff &");

    char passCommand[81] = "osascript ./EyeCript/utils/apple_scripts/choosePassword.applescript 2> /dev/null";
    FILE* pass = NULL;
    pass = popen(passCommand, "r");
    if (pass == NULL) {return -1;}

    char* password = malloc(sizeof(char) * 30);
    if (fgets(password, sizeof(char) * 30, pass) == NULL) {return -2;}

    return password;
}