#include "global_pipe.h"
#include "utils.h"
#include <unistd.h>

void encryption() {
    /*
    Encryption logic
    Get all needed data: file to encrypt
                         file to save it as
                         password for encryption
    */

    char new_filename[124];
    char filename[124];

    get_file();
    read_output(filename);

    get_new_file();
    read_output(new_filename);

    // Pipe to catch errors of encryption
    int fd_error[2] = {0};
    if (pipe(fd_error) != 0){
        bad_sound;
        visual_error;
        exit(2);
    }

    pid_t pid = fork();
    
    if (pid == 0) {
        // enc command 
        // openssl enc -aes-256-gcm -pbkdf2 -iter 600000 -salt -in <<get_file>> -out <<get_new_file>>
        dup2(fd_error[1], 2);
        close(fd_error[1]);
        close(fd_error[0]);
        dup2(fd[0], 0);
        close(fd[0]);
        close(fd[1]);
        get_password();
        execlp(
            "openssl",
            "openssl",
            "enc", "-aes-256-gcm", "-pbkdf2", "-iter", "600000", "-salt",
            "-in", filename,
            "-out", new_filename,
            "-pass:", "fd:0",
            NULL
        );
        bad_sound;
        visual_error;
        exit(4);
    }

    close(fd[1]);
    close(fd_error[1]);

    char er[1];
    if (read(fd_error[0], er, 1) == 0) {
        bad_sound;
        visual_error;
        exit(4);
    }

    // Add Extension in encrypted file footer
    char* extension = get_extension(filename);
    set_extension(new_filename, extension);
    free(extension);

    // Cleanup
    close(fd_error[0]);
    close(fd[0]);

    success_sound;
    visual_success;

    exit(0);

    return;
}