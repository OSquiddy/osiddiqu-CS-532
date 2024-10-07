/*
Name: Mohammed Omar Siddiqui
BlazerId: osiddiqu
Project #: 2
To compile: <instructions for compiling the program>
To run: <instructions to run the program>
*/

/**
 * TO DO
 * 
 * Sym Links - If a file is a sym link, show the file that it points to
 * Command line options - File should support flags. Order of flags should not matter
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

struct fileData {
    char path[1024];
    char name[256];
    char type[32];
    size_t size;
    int depth;
};

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

struct fileData* traverseDirectories(char *directory, int level, int *list_size, struct fileData *list) {
    struct dirent *dirent;
    struct stat buf;
    // struct fileData *newList;
    DIR *dir;

    dir = opendir(directory);
    if (dir == NULL) {
        perror("opendir");
        printf("Error opening directory '%s'\n", directory);
        exit(-1);
    }

    // printf("Directory opened\n");

    int count = 1;
    while ((dirent = readdir(dir)) != NULL) {

        if (strcmp(dirent->d_name, ".git") == 0 || strcmp(dirent->d_name, "..") == 0 || strcmp(dirent->d_name, ".") == 0) {
            continue;
        }

        char path[1024] = "";
        strncpy(path, directory, strlen(directory));
        strcat(path, "/");
        strcat(path, dirent->d_name);

        if (stat(path, &buf) < 0) {
            printf("stat error");
            perror("stat");
        }

        strncpy(list[*list_size - 1].path, path, strlen(path) + 1);
        strncpy(list[*list_size - 1].name, (*dirent).d_name, sizeof(dirent->d_name) + 1);
        strncpy(list[*list_size - 1].type, filetype(dirent->d_type), strlen(filetype(dirent->d_type)) + 1);
        list[*list_size - 1].size = buf.st_size;
        list[*list_size - 1].depth = level;
        // printf("Copied\n");
        ++*list_size;

        // printf("String: %s\n", list[*list_size - 1].path);


        // printf("New size: %d\n", *list_size);

        struct fileData *newList = realloc(list, *list_size * sizeof(struct fileData));
        if (newList == NULL) {
            printf("Cannot allocate more memory.\n");
            exit(-1);
        } else {
            list = newList;
        }

        for (int i = 2; i <= level; i++) {
            printf("\t");
        }
        // printf("[%d] %s (%s) (Size: %jd bytes)\n", count, dirent->d_name, filetype(dirent->d_type), buf.st_size);
        if (strcmp(filetype(dirent->d_type), "directory") == 0) {
            traverseDirectories(path, level + 1, list_size, list);
        }
        count++;
    }
    closedir(dir);
    
    return list;

}

int main (int argc, char **argv) {
    int level = 1;
    int opt;
    int list_size = 1;

    struct fileData *dataList;

    // printf("Size of struct: %ld\n", sizeof(struct fileData));

    dataList = malloc(list_size * 100 * sizeof(struct fileData));

    // printf("Size of dataList: %ld\n", sizeof(dataList[0]));

    if (argc < 1) {
        printf ("Usage: %s [dirname]\n", argv[0]);
        exit(-1);
    }

    while ((opt = getopt(argc, argv, "Srf:s:t:")) != -1) {
        printf("Opt value: %c, %d\n", opt, opt);
        printf("Opt value: %c, %d\n", opt, optind);
        switch (opt) {
            case 'S':
                
                break;
            case 's':
                break;
            case 'r':
                break;
            case 'f':
                break;
            case 't':
                break;
            default:
                fprintf(stderr, "Usage %s [-S] [-r] [-s sizeInBytes(int)] [-t d|f]\n", argv[0]);
                // exit(-1);
                break;
        }

    }

    // for (int i=0; i<argc; i++) {
    //     printf("Arg[%d]: %s\n", i, argv[i]);
    // }

    // printf("List size before traversing: %d\n", list_size);

    char starting_point[1024] = ".";

    if (argv[1]) {
        strncpy(starting_point, argv[1], sizeof(argv[1]));
        // printf("No argv[1]\n");
    }

    dataList = traverseDirectories(starting_point, level, &list_size, dataList);

    // printf("List size after traversing: %d\n", list_size);

    for (int i=list_size - 2; i>=0; i--) {
        printf("[%d] %s (%s) (Size: %jd bytes)\n", dataList[i].depth, dataList[i].name, dataList[i].type, dataList[i].size);
    }

    return 0;
}
