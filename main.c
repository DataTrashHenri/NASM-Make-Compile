#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>

#include "print.h"
#include "validate.h"
#include "read_from_bin.h"
#include "arg_interpretation.h"
#include "run_config.h"

int main(int argc,char** argv) {
    if (!valid_command(argc,argv)){
        log_error("Invalid operator, use \033[32mnmc help\033[31m for more details");
        return 1;
    }
    parse_command(argv);
    return 0;
}