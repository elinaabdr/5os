#include <stdio.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent *entry;

    if (argc != 2) {
        printf("Invalid args count!\n");
        printf("<Directory>\n");
        return 1;
    }

    dir = opendir(argv[1]);

    printf("Args directory \n");
    if (dir == NULL) {
        printf("Error opening directory");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    
    closedir(dir);
    dir = opendir(".");
    printf("\nCurrent directory \n");
    if (dir == NULL) {
        printf("Error opening directory");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
    return 0;
}