#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>
#include <stdio.h>
#include <stdbool.h>

#include "validate.h"

bool valid_input(int argc) {
    return argc > 1;
}
bool files_ok() {
    FILE *main = fopen("src/main.asm","r");
    if (main != NULL){
        fclose(main);
        return 1;
    }
    return 0;
}
bool folders_ok() {
    DIR *src = opendir("src");
    DIR *build = opendir("build");
    if (build && src){
        closedir(src);
        closedir(build);
        return 1;
    }
    closedir(src);
    closedir(build);
    return 0;
}