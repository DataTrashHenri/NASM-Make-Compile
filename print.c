#include "print.h"
#include <stdio.h>

void log_std(char *str) {
    printf("--> %s\n",str);
}
void log_error(char *str) {
    printf("--> \033[31m%s\033[0m\n",str);
}
