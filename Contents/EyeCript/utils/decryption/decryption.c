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
    read_output(filename);

    char* extension = get_extension(filename);

    // Generate Decrypted name
    char* new_filename = malloc(sizeof(char) * (strlen(filename) + strlen(extension) + 1));
    strcpy(new_filename, filename);
    strcat(new_filename, extension);

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

    pid_t pid = fork();
    
    if (pid == 0) {
        // enc command 
        // openssl enc -d -aes-256-gcm -pbkdf2 -iter 600000 -salt -in <<get_file>> -out <<get_new_file>>
        dup2(fd_error[1], 2);
        close(fd_error[1]);
        close(fd_error[0]);
        dup2(fd[0], 0);
        close(fd[0]);
        clsoe(fd[1]);
        get_password();
        execlp(
            "openssl",
            "openssl",
            "enc", "-d", "-aes-256-gcm", "-pbkdf2", "-iter", "600000", "-salt",
            "-in", filename,
            "-out", new_filename,
            "-pass:", "fd:0",
            NULL
        );
        bad_sound;
        visual_error;
        exit(4);
    }
    
    close(fd_error[1]);
    close(fd[1]);

    char er[1];
    if (read(fd_error[0], er, 1) == 0) {
        bad_sound;
        visual_wrong_pass;
        goto decryption;
    }

    // Cleanup
    free(extension);
    free(new_filename);

    close(fd_error[0]);
    close(fd[0]);

    success_sound;
    // visual_success;
    system(strcat("open ", new_filename));

    if (toggle == 0) {
        exit(0);
    } else if (toggle == 1) {
        system(strcat("rm ", new_filename));
    }
    exit(0);

    return;
}