#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

enum ResultCodes {
    SUCCESS,
    ERR_WRONG_PARAM_NUMBER,
    ERR_CANT_OPEN_FILE,
    ERR_CANT_CLOSE_FILE,
    ERR_CANT_WRITE_FILE,
    ERR_CANT_GET_FILE_STAT,
    ERR_CANT_SET_FILE_STAT
};

int main(int argc, char** argv) {
    int result_code = SUCCESS;

    if (argc != 3) {
        fprintf(stderr, "Wrong parameter count. Pass filenames to program\n");
        return ERR_WRONG_PARAM_NUMBER;
    }

    FILE* source_file = fopen(argv[1], "r");
    if (!source_file) {
        fprintf(stderr, "Can't open source file or file doesn't exist\n");
        return ERR_CANT_OPEN_FILE;
    }

    FILE* destination_file = fopen(argv[2], "w");
    if (!destination_file) {
        fprintf(stderr, "Can't open destination file or file doesn't exist\n");
        fclose(source_file);
        return ERR_CANT_OPEN_FILE;
    }

    int actual_char;
    while ((actual_char = fgetc(source_file)) != EOF) {
        if (fputc(actual_char, destination_file) == EOF) {
            fprintf(stderr, "Can't write data to file\n");
            result_code = ERR_CANT_WRITE_FILE;
            break;
        }
    }

    if (fclose(source_file) == EOF || fclose(destination_file) == EOF) {
        fprintf(stderr, "Error closing files\n");
        return ERR_CANT_CLOSE_FILE;
    }

    struct stat stat_source;
    if (stat(argv[1], &stat_source) == -1) {
        fprintf(stderr, "Can't get source file permissions\n");
        return ERR_CANT_GET_FILE_STAT;
    }

    if (chmod(argv[2], stat_source.st_mode) == -1) {
        fprintf(stderr, "Can't set destination file permissions\n");
        return ERR_CANT_SET_FILE_STAT;
    }

    printf("COPIED SUCCESSFULLY\n");
    return SUCCESS;
}
