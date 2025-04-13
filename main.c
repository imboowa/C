#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "file.h"

int main(int argc, char *argv[]) {
    struct stat fileStat = {0};
    Read_t read_t = {0};
    if(argc != 2){
        printf("Usage: %s <filename>\n", argv[0]);
        return 0;
    }
    int fd = open(argv[1],O_CREAT | O_RDWR,0644);
    if(fd == -1){
        printf("File Opening Failed\n");
        close(fd);
        return 0;
    }
    //char words[] = "Hello World\nThe File\n..........\n";
    //write(fd, words, strlen(words)); // write to file
    
    read(fd, &read_t, sizeof(read_t)); // read statistics
    
    printf("File version: %u\n", read_t.version);
    printf("FIle char: %u\n", read_t.numberOfEmployees);
    printf("File size: %u\n", read_t.filesize);
    
    
    if(fstat(fd, &fileStat) < 0){
        perror("fstat");
        close(fd);
        return 0;
    }
    if (foo(fileStat.st_size, read_t.filesize) == STATUS_BAD){
        printf("Problem: Corrupted File\n");
    }
    close(fd);
    return 0;
}
