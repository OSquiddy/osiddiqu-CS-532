
/* Sample C program to illustrate the use of opendir, readdir, and closedir
* system calls.
* This version prints the file type next to the file name.
*/
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

char *filetype(unsigned char type) {
    char *str;
    switch(type) {
        case DT_BLK: str = "block device"; break;
        case DT_CHR: str = "character device"; break;
        case DT_DIR: str = "directory"; break;
        case DT_FIFO: str = "named pipe (FIFO)"; break;
        case DT_LNK: str = "symbolic link"; break;
        case DT_REG: str = "regular file"; break;
        case DT_SOCK: str = "UNIX domain socket"; break;
        case DT_UNKNOWN: str = "unknown file type"; break;
        default: str = "UNKNOWN";
    }
    return str;
}

int traverseDirectories(char *directory, int level) {
    struct dirent *dirent;
    DIR *dir;

    dir = opendir(directory);
    if (dir == NULL) {
        perror("opendir");
        printf("Error opening directory '%s'\n", directory);
        exit(-1);
    }

    int count = 1;
    while ((dirent = readdir(dir)) != NULL) {

        if (strcmp(dirent->d_name, ".git") == 0 || strcmp(dirent->d_name, "..") == 0 || strcmp(dirent->d_name, ".") == 0) {
            continue;
        }

        char path[1024] = "";
        strncpy(path, directory, strlen(directory));
        strcat(path, "/");
        strcat(path, dirent->d_name);

        for (int i = 2; i <= level; i++) {
            printf("\t");
        }
        printf("[%d] %s (%s)\n", count, dirent->d_name, filetype(dirent->d_type));
        if (strcmp(filetype(dirent->d_type), "directory") == 0) {
            traverseDirectories(path, level + 1);
        }
        count++;
    }
    closedir(dir);
    
    return 0;

}

int main (int argc, char **argv) {
    int level = 1;
    if (argc < 2) {
        printf ("Usage: %s <dirname>\n", argv[0]);
        exit(-1);
    }

    traverseDirectories(argv[1], level);

    return 0;
}
