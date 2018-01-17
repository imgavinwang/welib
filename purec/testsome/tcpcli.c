/* tcpcli.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define DEFAULT_PORT 8800

int main(int argc, char** argv)
{
    int cPort = DEFAULT_PORT;
    int cClient = 0;
    int cLen = 0;
    struct sockaddr_in cli;
    char cbuf[4096] = {0};
    
    if(argc < 3) return 0;
    int port = atoi(argv[2]);
    
    memset(cbuf, 0, sizeof(cbuf));
    
    printf("%s:%d\n", argv[1], port);
    cli.sin_family = AF_INET;
    cli.sin_port = htons(port);
    cli.sin_addr.s_addr = INADDR_ANY;
    
    cClient = socket(AF_INET, SOCK_STREAM, 0);
    if(cClient < 0)
    {
        printf("socket() failure!\n");
        return -1; 
    }

    if(connect(cClient, (struct sockaddr*)&cli, sizeof(cli)) < 0)
    {
        printf("connect() failure!\n");
        return -1;
    }

    char data[]="Hello World!";  
    int sByte=send(cClient,data,strlen(data),0);
    if(sByte <= 0)  
    {  
        printf("send() failure\n");  
        return -1;  
    }  
    
    cLen = recv(cClient, cbuf, sizeof(cbuf),0);    
    if((cLen < 0)||(cLen == 0))
    {
          printf("recv() failure!\n");
        return -1;
    }
    printf("recv() Data From Server: [%s]\n", cbuf);
    
    close(cClient);
    
    return 0;
}