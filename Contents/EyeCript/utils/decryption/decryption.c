#include "global_pipe.h"
#include "utils.h"
#include <unistd.h>
#include <string.h>

extern int toggle;

void decryption() {
    /*
    Decryption logic
    Get all needed data: file to decrypt
                         file to save it as
                         password for encryption
    */

    char filename[124];

    get_file();
    wait(NULL);
    read_output(filename);

    char* extension = get_extension(filename);

    // Generate Decrypted name
    char* new_filename = malloc(sizeof(char) * (strlen(filename) + strlen(extension) + 1 + 1));
    strcpy(new_filename, filename);
    *(new_filename + strlen(filename)) = '.';
    *(new_filename + strlen(filename) + 1) = '\0';
    strcat(new_filename, extension);

    FILE* new_file = fopen(new_filename, "rb+");
    if (new_file != NULL) {
        if (truncate(new_filename, 0) == -1) {
            bad_sound;
            visual_error;
            exit(2);
        }
        fclose(new_file);
    }

    // Decryption -----------------------
    // Pipe to catch errors of encryption
    int fd_error[2] = {0};
    if (pipe(fd_error) != 0){
        bad_sound;
        visual_error;
        exit(2);
    }

    decryption:
    
    init_pipe();
    get_password();

    pid_t pid = fork();
    
    if (pid == 0) {
        // enc command 
        // openssl enc -d -aes-256-gcm -pbkdf2 -iter 600000 -salt -in <<get_file>> -out <<get_new_file>>
        dup2(fd_error[1], 2);
        close(fd_error[1]);
        close(fd_error[0]);
        dup2(fd[0], 0);
        close(fd[0]);
        wait(NULL);
        execlp(
            "openssl",
            "openssl",
            "enc", "-d", "-aes-256-gcm", "-pbkdf2", "-iter", "600000", "-salt",
            "-in", filename,
            "-out", new_filename,
            "-pass", "fd:0",
            NULL
        );
        bad_sound;
        visual_error;
        exit(4);
    }
    wait(NULL);
    
    close(fd_error[1]);

    char er[1];
    if (read(fd_error[0], er, 1) == 0) {
        bad_sound;
        visual_wrong_pass;
        goto decryption;
    }

    // Cleanup
    close(fd_error[0]);
    close(fd[0]);

    success_sound;
    pid = fork();
    if (pid < 0) {
        bad_sound;
    }
    if (pid == 0) {
        execlp(
            "open",
            "open",
            new_filename,
            NULL
        );
        bad_sound;
        visual_error;
    }
    wait(NULL);

    // Cleanup
    free(extension);
    free(new_filename);

    if (toggle == 0) {
        exit(0);
    } else if (toggle == 1) {
        system(strcat("rm ", new_filename));
    }
    exit(0);

    return;
}