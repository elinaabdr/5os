#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

int CheckDirectory(char *argv[], FILE *f)
{
    char absolutePath[PATH_MAX];
    char *resolvedPath = realpath(argv[1], absolutePath);
    if (resolvedPath) {
        argv[1] = resolvedPath;
    } else {
        printf("Could not construct absolute path to directory\n");
        return 1;
    }
    
    struct dirent *entry;

    DIR *dr = opendir(argv[1]); 
    
    if (dr == NULL) { 
        printf("Could not open directory %s\n", argv[1]);
        return 0;
    }

    int min = atoi(argv[2]);
    int max = atoi(argv[3]);

    int countFiles = 0;
    while ((entry = readdir(dr)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue; 
        }

        char fullPath[PATH_MAX];
        snprintf(fullPath, PATH_MAX, "%s/%s", argv[1], entry->d_name);

        if (entry->d_type == DT_DIR) {
            char *myArgs[] = {"", fullPath, argv[2], argv[3], argv[4]};
            countFiles += CheckDirectory(myArgs, f);
            
        } else {
            struct stat fileStat;
            if (stat(fullPath, &fileStat) == 0) {
                if (fileStat.st_size >= min && fileStat.st_size <= max) {
                    fprintf(f, "%s\n", fullPath);
                }
                countFiles++;
            }
        }
    }

    closedir(dr); 

    return countFiles;
}

int main(int argc, char *argv[]) {
     if (argc != 5)
    {
        printf("Invalid args count!\n");
        printf("<Directory search> <min size> <max size> <file out>\n");
        return 1;
    }

    FILE *f = fopen(argv[4], "w");

    if (f == NULL)
    {
        printf("Invalid file out name!\n");
    }

    char absolutePath[PATH_MAX];
    char *resolvedPath = realpath(argv[1], absolutePath);
    if (resolvedPath) {
        argv[1] = resolvedPath;
    } else {
        printf("Could not construct absolute path to directory\n");
        return 1;
    }
    printf("Count looked files = %d\n", CheckDirectory(argv, f));

    fclose(f);

    return 0;
}