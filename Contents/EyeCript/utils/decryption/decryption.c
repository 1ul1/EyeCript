#include "global_pipe.h"
#include "utils.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

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

    // Generate Decrypted name
    char* new_filename = malloc(sizeof(char) * (strlen(filename) + 1 + 1));
    strcpy(new_filename, filename);
    *(new_filename + strlen(filename)) = '.';
    *(new_filename + strlen(filename) + 1) = '\0';

    // Clean and check if it already exists/
    if (access(new_filename, F_OK) == 0) {
        bad_sound;
        visual_error;

        perror("File already exists");
        exit(2);
    }

    // Decryption -----------------------
    decryption:

    // Pipe to catch errors of encryption

    init_pipe();
    int fd_error[2];
    if (pipe(fd_error) != 0){
        bad_sound;
        visual_error;

        perror("Pipe fd_error Failed");
        exit(2);
    }
    
    // Exit if user closes applescript
    if (get_password() == 8) {
        remove(new_filename);
        exit(8);
    }

    pid_t pid = fork();
    
    if (pid == 0) {
        // enc command 
        // openssl enc -d -aes-256-gcm -pbkdf2 -iter 600000 -salt -in <<get_file>> -out <<get_new_file>>
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
            "enc", "-d", "-aes-256-cbc", "-pbkdf2", "-iter", "600000", "-salt",
            "-in", filename,
            "-out", new_filename,
            "-pass", "fd:0",
            NULL
        );
        bad_sound;
        visual_error;
        perror("Openssl failed");
        exit(4);
    }
    wait(NULL);

    close(fd[0]);
    close(fd_error[1]);

    char er[13];
    if (read(fd_error[0], er, 12) > 0) {
        bad_sound;
        visual_wrong_pass;
        close(fd_error[0]);
        goto decryption;
    }

    close(fd_error[0]);

    // remove extension from footer, add it to file
    char* extension = get_extension(new_filename);

    char* new_filename_extension = malloc(
        sizeof(char) * (strlen(new_filename) + strlen(extension) + 1)
    );
    *new_filename_extension = '\0';
    strcat(new_filename_extension, new_filename);
    strcat(new_filename_extension, extension);

    // Check if it already exists to not replace other files
    if (access(new_filename_extension, F_OK) == 0 && *extension != '\0') {
        remove(new_filename);
        
        bad_sound;
        visual_error;
        perror("File already exists");
        exit(2);
    }

    if (rename(new_filename, new_filename_extension) != 0) {
        bad_sound;
        visual_error;

        perror("rename failed");
        exit(4);
    }

    free(extension);

    // Cleanup
    success_sound;
    pid = fork();
    if (pid < 0) {
        bad_sound;
    }
    if (pid == 0) {
        execlp(
            "open",
            "open",
            "-W",
            new_filename_extension,
            NULL
        );
        bad_sound;
        visual_error;
        perror("open failed");
        exit(4);
    }
    wait(NULL);

    // Cleanup
    if (toggle == 0) {
        exit(0);
    } else if (toggle == 1) {
        sleep(3);
        remove(new_filename_extension);
    }

    free(new_filename);
    free(new_filename_extension);

    exit(0);

    return;
}