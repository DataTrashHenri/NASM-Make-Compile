#include <stdio.h>
#include <stdlib.h>

#include "read_from_bin.h"

void read_bin_int() {
    FILE *ptr;
    ptr = fopen("./build/out.bin","rb");
    
    fseek(ptr, 0, SEEK_END);
    long fsize = ftell(ptr);
    long longs = fsize/8;
    rewind(ptr);

    long *buffer = malloc(fsize);
    fread(buffer,sizeof(buffer),longs,ptr);
    printf("\033[33m%li\033[0m integer(s)->\n",longs);
    for (int i = 0; i < longs;i++) {
        printf("int(%i)= \033[32m%li\033[0m\n",i,buffer[i]);
    }
    fclose(ptr);
    free(buffer);
}
void read_bin_float() {
    FILE *ptr;
    ptr = fopen("./build/out.bin","rb");
    
    fseek(ptr, 0, SEEK_END);
    long fsize = ftell(ptr);
    long floats = fsize/sizeof(double);
    rewind(ptr);

    double *buffer = malloc(fsize);
    fread(buffer,sizeof(buffer),floats,ptr);
    printf("\033[33m%li\033[0m float(s)->\n",floats);
    for (int i = 0; i < floats;i++) {
        printf("float(%i)= \033[32m%.15f\033[0m\n",i,buffer[i]);
    }
    fclose(ptr);
    free(buffer);
}
void read_bin_bitwise() {
    FILE *ptr;
    ptr = fopen("./build/out.bin","rb");
    
    fseek(ptr, 0, SEEK_END);
    long fsize = ftell(ptr);
    long bytes = fsize/sizeof(char);
    rewind(ptr);

    char *buffer = malloc(fsize);
    fread(buffer,sizeof(buffer),bytes,ptr);
    
    for (int i = 0; i < bytes; i++) {
        printf("byte(%i)= \033[32m", i);

        for (int bit = 0; bit < 8; bit++) {
            printf("%i", (buffer[i] >> bit) & 1);
        }

        printf("\033[0m\n");
    }
    fclose(ptr);
    free(buffer);
}