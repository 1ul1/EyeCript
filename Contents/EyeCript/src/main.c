#include "global_pipe.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    // Starting point of project
    
    init_pipe();
    if (argc != 2) {
        bad_sound;
        visual_error;
        exit(2);
    }

    const char* options[] = {"enc", "dec", "view"};
    const char* option = argv[1];

    for (int i = 0; i < 3; i++) {
        if (strcmp(option, *(options + i)) == 0) {
            switch (i) {
            case 0:
                encryption();
                break;
            case 1:
                decryption();
                break;
            case 2:
                preview();
                break;
            default:
                bad_sound;
                visual_error;
                exit(2);
            }
        }
    }

    success_sound;
    visual_success;

    exit(0);


    return 0;
}