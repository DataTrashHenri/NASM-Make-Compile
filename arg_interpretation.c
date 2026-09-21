#include <stdbool.h>
#include <string.h>

#include "arg_interpretation.h"
#include "run_config.h"

char *base_cmds[] = {"init","help","run","status","fuckitall"};
char *run_cmds[] = {"int","float"};

bool valid_argc(int argc) {
    return argc>1;
}
bool equal(char *str1,char *str2) {
    return !strcmp(str1,str2);
}
bool contains(char * arr[], int arr_len, char* element) {
    for ( int i = 0; i<arr_len;i++) {
        if (equal(arr[i],element))
            return 1;
    }
    return 0;
}
bool validate(char *pre,char *cur,char *next) {
    if (equal(pre,"")) {
        if (!contains(base_cmds,5,cur))
            return 0;
        else {
            return validate(cur,next,"");  
        }
    }
    return 1;
}

bool valid_command(int argc, char **argv) {
    if (!valid_argc(argc)) return 0;

    return validate("",argv[1],argv[2]);
}
void parse_command(char **argv) {
    if (equal(argv[1],"status")) {
        run_status();
    }
    else if (equal(argv[1],"init")) {
        run_init();
    }
    else if (equal(argv[1],"help")) {
        run_help();
    }
    else if (equal(argv[1],"run")) {
        run_run(argv[2]);
    }
    else if (equal(argv[1],"fuckitall")) {
        run_fuckitall();
    }
    else {
        return;
    }
}
