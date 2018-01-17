#include <sys/select.h>
#include <sys/socket.h>
#include <stdio.h>
#define NUM 2000
int fds[NUM];


int main()
{
    printf("%d", FD_SETSIZE);
}