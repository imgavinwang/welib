//netgene@hotmail.com
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define EHCO_PORT 8080

//singe process to do blocking io.
int main(int argc, char **argv)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in sa;
    bzero(&sa, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(EHCO_PORT);

	bind(sock, (struct sockaddr *)&sa, sizeof(sa));
	listen(sock, 1024);

	for(;;) {
		printf("accept start\n");
		int fd = accept(sock, NULL, NULL);
		printf("accept fd:%d\n", fd);
		char buff[100];
		printf("read start\n");
		int n = read(fd, &buff, 100);
		printf("read end\n");
		if(n > 0) {
		write(fd, buff, n);
		}
		printf("close fd:%d\n", fd);
		close(fd);
	}

	return 0;
}
