#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
bool valid_input(int argc,char** argv) {
    return argc > 1;
}
void error_log(char* str) {
    printf("nmc errorlog: \"%s\"\n",str);
}
void service_log(char* str) {
    printf("-->%s<--\n",str);
}
void read_int_from_bin() {
    FILE *ptr;
    ptr = fopen("./build/out.bin","rb");
    
    fseek(ptr, 0, SEEK_END);
    long fsize = ftell(ptr);
    long longs = fsize/8;
    rewind(ptr);

    long *buffer = malloc(fsize);
    fread(buffer,sizeof(buffer),longs,ptr);
    printf("%li integer(s) found->\n",longs);
    for (int i = 0; i < longs;i++) {
        printf("int(%i)= %li\n",i,buffer[i]);
    }
    free(ptr);
    free(buffer);
}
void read_float_from_bin() {
    FILE *ptr;
    ptr = fopen("./build/out.bin","rb");
    
    fseek(ptr, 0, SEEK_END);
    long fsize = ftell(ptr);
    long floats = fsize/4;
    rewind(ptr);

    float *buffer = malloc(fsize);
    fread(buffer,sizeof(buffer),floats,ptr);
    printf("%li float(s) found->\n",floats);
    for (int i = 0; i < floats;i++) {
        printf("int(%i)= %f\n",i,buffer[i]);
    }
    free(ptr);
    free(buffer);
}
int main(int argc,char** argv) {
    if (!valid_input(argc,argv)){
        error_log("--help for commands");
        return 1;
    }
    if(!strcmp(argv[1],"--help")) {
        printf("- nmc init for new project\n");
        printf("- nmc compile to compile\n");
        printf("- nmc run to compile & run\n");
        printf("- nmc fuckitall to delete the project\n");
    } else if (!strcmp(argv[1],"init")) {
        system("mkdir src");
        system("mkdir build");
        system("touch ./src/main.asm");
        system("echo \"global _start\n_start: mov rax,60\n mov rdi,42\nsyscall\" > ./src/main.asm");
        service_log("folder structure established.");
        service_log("main.asm as sample created");
        service_log("to run this project, use nmc run");
    } else if (!strcmp(argv[1],"fuckitall")) {
        system("rm -fr build src out");
        service_log("removed build and source folders");
    } else if (!strcmp(argv[1],"run")) {
        system("nasm -felf64 ./src/main.asm -o ./build/main.o");
        system("ld ./build/main.o -o out");
        service_log("Execution started");
        system("./out > ./build/out.bin");
        service_log("Execution finished");
        printf("Extracted binarycontent:\n");
        read_int_from_bin();
    }    
    else {
        error_log("Unknown command, use --help for more info\n");
    }
    return 0;
}