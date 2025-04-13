#include <stdio.h>
#include <stdlib.h>

typedef enum{
    STATUS_GOOD,
    STATUS_BAD,
} __attribute__((__packed__)) Status_e; // attribute packed prevents addons by other OS

Status_e foo(int **data, int);
int main(int argc, char *argv[]){
    int *first = malloc(32);
    if (first == NULL){
        return -1;
    }
    if(foo(&first, 64) == STATUS_BAD){
        printf("STATUS BAD\n");
        return -1;
    }
    printf("STATUS GOOD\n...........\n");
    free(first);
    first = NULL;
    return 0;
}
Status_e foo(int **data, int len){
    int *temp = NULL;
    temp = realloc(*data, len);
    if(temp == NULL){
        *data = NULL;
        free(temp);
        temp = NULL;
        return STATUS_BAD;
    }
    *data = temp;
    free(temp);
    temp = NULL;
    return STATUS_GOOD;
}
