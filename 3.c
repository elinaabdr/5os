#include <stdio.h>
#include <stdlib.h>

enum ResultCodes {
    SUCCESS = 0,
    ERR_WRONG_PARAM_NUMBER = 1,
    ERR_CANT_OPEN_FILE = 2,
    ERR_CANT_CLOSE_FILE = 3
};

int main(int argc, char** argv) {
    int result_code = SUCCESS;

    if (argc != 3) {
        fprintf(stderr, "Invalid parameter count. Please provide a filename.\n");
        return ERR_WRONG_PARAM_NUMBER;
    }

    FILE* file = fopen(argv[1], "r");

    if (!file) {
        fprintf(stderr, "Unable to open the specified file or the file does not exist.\n");
        return ERR_CANT_OPEN_FILE;
    }

    fprintf(stdout, "File content:\n");

    char current_char;
    int count = 0;
    int group_size = atoi(argv[2]);

    while ((current_char = fgetc(file)) != EOF) {
        putchar(current_char);

        if (current_char == '\n') {
            count++;

            if (group_size > 0 && count == group_size) {
                printf("PRESS ANY KEY TO CONTINUE...\n");
                getchar();
                count = 0;
            }
        }
    }

    if (result_code) {
        return result_code;
    }

    result_code = fclose(file);

    if (result_code == EOF) {
        fprintf(stderr, "Unable to close the file.\n");
        return ERR_CANT_CLOSE_FILE;
    }

    return SUCCESS;
}
