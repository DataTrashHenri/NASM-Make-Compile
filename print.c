#include <stdio.h>
#include <dirent.h>

#include "print.h"

void log_std(char *str) {
    printf("--> %s\n",str);
}
void log_error(char *str) {
    printf("--> \033[31m%s\033[0m\n",str);
}
void print_dir_content(char *src) {
    DIR* dir = opendir(src);
    if (dir == NULL) printf("shit\n");
    struct dirent *entry;
    while((entry = readdir(dir))!= NULL) {
        if (entry->d_type == DT_REG && entry->d_name[0] != '.')
            printf("✓ %s\n",entry->d_name);
    }
    closedir(dir);
}
