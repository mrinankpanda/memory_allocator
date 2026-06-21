#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <errno.h>
#include "birchutils.h"

#define packed __attribute__((__packed__))
#define unused __attribute__((__unused__))
#define maxWords ((1024*1024*1024/4)-1)

#define errNoMem 1

typedef unsigned char int8;
typedef unsigned short int int16; 
typedef unsigned int int32;
typedef unsigned long long int int64; 
typedef _BitInt(128) int128;
typedef void heap; 
typedef int32 word; 

struct packed s_header {
    word w:30;
    bool allocated:1;
    bool unused reserved:1; 
}; 

typedef struct packed s_header header; 

#define $1 (int8 *)
#define $2 (int16)
#define $4 (int32)
#define $8 (int64)
#define $16 (int128)
#define $c (char *)
#define $i (int)
#define $v (void *)
#define $h (header *)

#define reterr(x) errno = (x); return $v 0

void *mkalloc(word words, header *hdr);
void *alloc(int32); 
int main(int, char**); 