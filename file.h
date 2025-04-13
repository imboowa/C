#ifndef FILE_H
#define FILE_H

/*
 struct makes variables
 struct receives data
 struct populated -> stat
 */
typedef struct{
    unsigned short version;
    unsigned short numberOfEmployees;
    unsigned int filesize;
} __attribute__((__packed__)) Read_t;

/*
 enum stores status
 */
typedef enum {
    STATUS_GOOD,
    STATUS_BAD
} Status_e;

/*
 func compares stat size and file read size
 func returns status good for equality in status size and file read size
 */
Status_e foo(ssize_t statSize, int filesize);

#endif
