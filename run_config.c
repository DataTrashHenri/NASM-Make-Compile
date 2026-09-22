#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "run_config.h"
#include "print.h"
#include "validate.h"
#include "read_from_bin.h"

void run_status(){
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
}
void run_init() {
    system("mkdir src");
    system("mkdir build");
    system("touch ./src/main.asm");
    system("echo \"global _start\n_start: mov rax,60\n mov rdi,42\nsyscall\" > ./src/main.asm");
    log_std("folder structure established.");
    log_std("main.asm as sample created");
    log_std("to run this project, use nmc run");
}
void run_fuckitall() {
    system("rm -fr build src out");
    log_std("removed build and source folders");
}
void run_help() {
        printf("- \033[32mnmc init\033[0m for new project\n");
        printf("- \033[32mnmc run [int/float](optional)\033[0m to compile & run\n");
        printf("- \033[32mnmc fuckitall\033[0m to delete the project\n");
        printf("- \033[32mnmc status\033[0m to check wheter project was set up correctly\n");
}
void run_run(char *opt) {
    struct timespec start, end;
    system("nasm -felf64 ./src/main.asm -o ./build/main.o");

    system("nasm -felf64 ~/nmc/libs/pout.asm -o ./build/pout.o");
    system("nasm -felf64 ~/nmc/libs/alloc.asm -o ./build/alloc.o");
    system("nasm -felf64 ~/nmc/libs/sqrt.asm -o ./build/sqrt.o");
    system("nasm -felf64 ~/nmc/libs/sieve.asm -o ./build/sieve.o");
    
    system("ld ./build/*.o -o out");

    log_std("performance-run started");
    clock_gettime(CLOCK_MONOTONIC, &start);
    system("./out > /dev/null");
    clock_gettime(CLOCK_MONOTONIC, &end);
    log_std("performance-run ended");
    double elapsed_ms =
    (end.tv_sec - start.tv_sec) * 1000.0 +
    (end.tv_nsec - start.tv_nsec) / 1e6;
    printf("execution time: %.3f ms ( ~\033[32m%.3fms\033[0m pure asm)\n", elapsed_ms,(elapsed_ms-0.350));
    
    log_std("Execution started");
    system("./out > ./build/out.bin");
    log_std("Execution finished");
    if(opt != NULL) {
        if(!strcmp(opt,"int"))
            read_bin_int();
        else if (!strcmp(opt,"float"))
            read_bin_float();
        else if (!strcmp(opt,"bit"))
            read_bin_bitwise();
        else if (!strcmp(opt,"all")) {
            read_bin_float();
            read_bin_int();
            read_bin_bitwise();
        }
        else log_std("unkonw type to convert");
    }
}