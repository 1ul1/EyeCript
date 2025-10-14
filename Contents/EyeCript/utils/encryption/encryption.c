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
    get_file();
    get_new_file();

    char filename[124];
    char password[32];
    char new_filename[124];

    ssize_t len = 0;

    len = read(fd[0], filename, sizeof(filename) - 1);
    if (len <= 0){
        exit(3);
    }
    filename[len] = '\0';

    len = read(fd[0], new_filename, sizeof(new_filename) - 1);
    if (len <= 0){
        exit(3);
    }
    new_filename[len] = '\0';



    // Pipe to catch errors of encryption
    int fd_error[2] = {0};
    if (pipe(fd_error) != 0)
        exit(2);

    pid_t pid = fork();
    
    if (pid == 0) {
        // enc command 
        // openssl enc -aes-256-gcm -pbkdf2 -iter 600000 -salt -in <<get_file>> -out <<get_new_file>>
        dup2(fd_error[1], 2);
        close(fd_error[1]);
        dup2(fd[0], 0);
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
    } else
        exit(1);

    char er[1];
    if (read(fd_error[0], er, 1) == 0) {
        system("osascript -e 'display dialog \"Da\"'");
        exit(4);
    }

    close(fd_error[0]);
    close(fd[0]);
    close(fd[1]);
    exit(0);

    return;
}