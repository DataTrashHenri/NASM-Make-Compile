#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>

#include "print.h"
#include "validate.h"
#include "read_from_bin.h"

bool valid_input(int argc,char** argv) {
    return argc > 1;
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
int main(int argc,char** argv) {
    if (!valid_input(argc,argv)){
        log_error("--help for commands");
        return 1;
    }
    if(!strcmp(argv[1],"help")) {
        printf("- \033[32mnmc init\033[0m for new project\n");
        printf("- \033[32mnmc run\033[0m to compile & run\n");
        printf("- \033[32mnmc fuckitall\033[0m to delete the project\n");
        printf("- \033[32mnmc status\033[0m to check wheter project was set up correctly\n");
    } else if (!strcmp(argv[1],"init")) {
        system("mkdir src");
        system("mkdir build");
        system("touch ./src/main.asm");
        system("echo \"global _start\n_start: mov rax,60\n mov rdi,42\nsyscall\" > ./src/main.asm");
        log_std("folder structure established.");
        log_std("main.asm as sample created");
        log_std("to run this project, use nmc run");
    } else if (!strcmp(argv[1],"fuckitall")) {
        system("rm -fr build src out");
        log_std("removed build and source folders");
    } else if (!strcmp(argv[1],"run")) {
        system("nasm -felf64 ./src/main.asm -o ./build/main.o");
        system("nasm -felf64 ~/nmc/libs/pout.asm -o ./build/pout.o");
        system("ld ./build/main.o ./build/pout.o -o out");
        log_std("Execution started");
        system("./out > ./build/out.bin");
        log_std("Execution finished");
        if(argc>2) {
            printf("Extracted binarycontent:\n");
            if(!strcmp(argv[2],"ints"))
                read_bin_int();
            else if (!strcmp(argv[2],"floats"))
                read_bin_float();
            else if (!strcmp(argv[2],"all")) {
                read_bin_float();
                read_bin_int();
            }
            else log_error("either unkonw or not yet implemented type");
        }
    }
    else if (!strcmp(argv[1],"status")) {
        if (folders_ok()) {
            log_std("folder structure   OK");
        } else {
            log_error("folder structure   MISSING");
        }
        if(files_ok()) {
            log_std("assembly files     OK");
        } else {
            log_error("assembly files     NOT_FOUND");
        }
        printf("\nincluded libaries:\n");
        print_dir_content("/root/nmc/libs/");

    } else {
        log_error("Unknown command, use help for more info\n");
    }
    return 0;
}