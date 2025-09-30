#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

char* get_file() {
    // Uses applescript to prompts the user to select 
    // a file and returns the full absolute path
    system("afplay /System/Library/Sounds/Glass.aiff &");

    char nameCommand[107] = "osascript ./EyeCript/utils/apple_scripts/selectFile.applescript 2> /dev/null";
    FILE* nameFile = NULL;
    nameFile = popen(nameCommand, "r");
    if (nameFile == NULL) {return -3;}

    char* path = malloc(sizeof(char) * 256);
    if (fgets(path, sizeof(char) * 256, nameFile) == NULL) {return -4;}
    
    return path;
}