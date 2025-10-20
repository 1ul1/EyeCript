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

    // char* extension = get_extension(filename);

    // Generate Decrypted name
    char* new_filename = malloc(sizeof(char) * (strlen(filename) + 1 + 1));
    strcpy(new_filename, filename);
    *(new_filename + strlen(filename)) = '.';
    // *(new_filename + strlen(filename) + 1) = '\0';
    // strcat(new_filename, extension);

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
    decryption:

    // Pipe to catch errors of encryption

    init_pipe();
    int fd_error[2];
    if (pipe(fd_error) != 0){
        bad_sound;
        visual_error;
        exit(2);
    }
    
    get_password();

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
            new_filename,
            NULL
        );
        bad_sound;
        visual_error;
    }
    wait(NULL);

    // Cleanup
    if (toggle == 0) {
        exit(0);
    } else if (toggle == 1) {
        char* rm_command = malloc(sizeof(char)* (strlen(new_filename) + 4));
        *rm_command = '\0';
        system(strcat(strcat(rm_command, "rm "), new_filename));
        free(rm_command);
    }

    free(new_filename);

    exit(0);

    return;
}