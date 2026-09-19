#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
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
    printf("%li integer(s)->\n",longs);
    for (int i = 0; i < longs;i++) {
        printf("int(%i)= %li\n",i,buffer[i]);
    }
    fclose(ptr);
    free(buffer);
}
void read_float_from_bin() {
    FILE *ptr;
    ptr = fopen("./build/out.bin","rb");
    
    fseek(ptr, 0, SEEK_END);
    long fsize = ftell(ptr);
    long floats = fsize/sizeof(double);
    rewind(ptr);

    double *buffer = malloc(fsize);
    fread(buffer,sizeof(buffer),floats,ptr);
    printf("%li float(s)->\n",floats);
    for (int i = 0; i < floats;i++) {
        printf("float(%i)= %.12f\n",i,buffer[i]);
    }
    fclose(ptr);
    free(buffer);
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
bool files_ok() {
    FILE *main = fopen("src/main.asm","r");
    if (main != NULL){
        fclose(main);
        return 1;
    }
    return 0;
}
int main(int argc,char** argv) {
    if (!valid_input(argc,argv)){
        error_log("--help for commands");
        return 1;
    }
    if(!strcmp(argv[1],"--help")) {
        printf("- nmc init for new project\n");
        printf("- nmc run to compile & run\n");
        printf("- nmc fuckitall to delete the project\n");
        printf("- nmc git xx for basic git usage\n");
        printf("- nmc status to check wheter project was set up correctly\n");
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
        if(argc>2) {
            printf("Extracted binarycontent:\n");
            if(!strcmp(argv[2],"ints"))
                read_int_from_bin();
            else if (!strcmp(argv[2],"floats"))
                read_float_from_bin();
            else if (!strcmp(argv[2],"all")) {
                read_float_from_bin();
                read_int_from_bin();
            }
            else error_log("either unkonw or not yet implemented type");
        }
    }    
    else if (!strcmp(argv[1],"status")) {
        if (folders_ok()) {
            service_log("folder structure   OK");
        } else {
            error_log("missing folders..");
        }
        if(files_ok()) {
            service_log("assembly files     OK");
        } else {
            error_log("missing any assembly files");
        }
    }
    else if (!strcmp(argv[1],"git")) {
        if (argc < 3) {
            error_log("missing statement");
        } else {
            char cmd[99];
            if (argc ==3)
                sprintf(cmd,"git %s",argv[2]);
            if (argc ==4)
                sprintf(cmd,"git %s %s",argv[2],argv[3]);
            system(cmd);
        }
    }
    else {
        error_log("Unknown command, use --help for more info\n");
    }
    return 0;
}