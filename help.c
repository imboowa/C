#include <stdio.h> // input - output
#include <string.h> // for strlen
#include <fcntl.h> // for open
#include <unistd.h> // for write
#include <sys/stat.h> // for stat
#include <sys/types.h>

typedef struct {
    unsigned short version;
    unsigned short employees;
    unsigned int filesize;
} __attribute__((__packed__)) data_header_t; // prevent addons by other OS

int main(int argc, char *argv[]){
    data_header_t head_t = {0};
    struct stat dbStat = {0}; // arguments received in commandline
    if (argc != 2){
        printf("Usage : %s <filename>\n", argv[0]); // show how to use program
        return 0; // exit programm successully (fullstop)
    }
    int fd = open(argv[1], O_RDWR | O_CREAT, 0644); // open file at argument[1]
    // create it if not there or open it then permissions O_RDONLY for group and others but O_RDWR for you
    if (fd == -1){ // if -1 from open then printf error
        perror("open");
        return -1; // exit successfully
    }
    //char mydata[] = "Hello World\nI am Coding\nIt is fun...\nThis file has been compiled\nIn C\nByeee\n";
    //write(fd, &mydata, strlen(mydata)); // write to pointer file descriptor the strings at the memory address of lenght 'n'
    // reading files
    //char output[100];
    //ssize_t byteToRead = read(fd, &output, sizeof(output));
    if (read(fd, &head_t, sizeof(head_t)) == -1){
        perror("read");
        close(fd);
        return -1;
    }
    //output[byteToRead] = '\0'; // set last character to null(terminate)
    printf("Version: %u\n", head_t.version);
    printf("No. of Employees: %u\n", head_t.employees);
    printf("File size: %u\n", head_t.filesize);
    
    off_t st_s = fstat(fd, &dbStat);
    if(st_s < 0){
        perror("fstat");
        return -1;
    }
    printf("DB Stat size report: %lld\n", dbStat.st_size);
    if (dbStat.st_size != head_t.filesize){
        printf("GOWAY HACKER!\n");
        close(fd);
        return -1;
    }
    close(fd); // close the file
    return 0;
}
