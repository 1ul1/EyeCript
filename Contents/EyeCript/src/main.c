#include "global_pipe.h"
#include <stdlib.h>

int main() {
    // Starting point of project
    // Triggers Applescript UI to select wanted function
    
    init_pipe();

    system("afplay /System/Library/Sounds/Glass.aiff &");

    execlp(
        "osascript",
        "osascript",
        "./EyeCript/utils/apple_scripts/options.applescript",
        NULL
    );
}