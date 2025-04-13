#include <stdio.h>
#include <stdlib.h>
#include "file.h"

Status_e foo(ssize_t statSize, int filesize){
    if(statSize == filesize){
        printf("File Match\n");
        return STATUS_GOOD;
    }
    return STATUS_BAD;
}
