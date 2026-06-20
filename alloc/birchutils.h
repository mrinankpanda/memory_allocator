/* birchutils.h */
#ifndef Birchutils
#define Birchutils

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;

int8 *todotted(in_addr_t);
void zero(int8*,int16);

#endif /* Birchutils */