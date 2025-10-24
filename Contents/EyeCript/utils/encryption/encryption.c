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
    wait(NULL);
    read_output(filename);

    get_new_file();
    wait(NULL);
    read_output(new_filename);

    // Clean new_file
    FILE* new_file = fopen(new_filename, "rb+");
    if (new_file != NULL) {
        if (truncate(new_filename, 0) == -1) {
            bad_sound;
            visual_error;
            perror("Truncate failed");
            exit(2);
        }
        fclose(new_file);
    }

    // Pipe to catch errors of encryption
    int fd_error[2] = {0};
    if (pipe(fd_error) != 0){
        bad_sound;
        visual_error;
        perror("Pipe init failed");
        exit(2);
    }

    // Add Extension in original file's footer
    char* extension = find_extension(filename);
    set_extension(filename, extension);
    free(extension);

    init_pipe();
    
    // Exit if user closes applescript
    if (get_password() == 8) {
        get_extension(filename);
        exit(8);
    }

    pid_t pid = fork();
    if (pid == 0) {
        // enc command 
        // openssl enc -aes-256-gcm -pbkdf2 -iter 600000 -salt -in <<get_file>> -out <<get_new_file>>
        dup2(fd_error[1], 2);
        if (fd_error[1] > 2)
            close(fd_error[1]);
        if (fd_error[0] > 2)
            close(fd_error[0]);
        dup2(fd[0], 0);
        if (fd[0] > 2)
            close(fd[0]);
        execlp(
            "openssl",
            "openssl",
            "enc", "-aes-256-cbc", "-pbkdf2", "-iter", "600000", "-salt",
            "-in", filename,
            "-out", new_filename,
            "-pass", "fd:0",
            NULL
        );
        bad_sound;
        visual_error;
        perror("Openssl failed I");
        exit(4);
    }
    wait(NULL);

    close(fd_error[1]);
    close(fd[0]);

    // Delete Extension from original file's footer
    get_extension(filename);

    char er[12];
    if (read(fd_error[0], er, 11) > 0) {
        remove(new_filename);

        bad_sound;
        visual_error;
        perror("openssl encryption failed II");
        exit(4);
    }

    // Cleanup
    close(fd_error[0]);
    close(fd[0]);

    success_sound;
    visual_success;

    exit(0);

    return;
}