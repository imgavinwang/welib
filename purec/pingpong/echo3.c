//netgene@hotmail.com
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define EHCO_PORT 8080

//super process accept and fork child to do blocking io.
int main(int argc, char **argv)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in sa;
    bzero(&sa, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(EHCO_PORT);

	bind(sock, (struct sockaddr *)&sa, sizeof(sa));
	if(listen(sock, 1024) < 0) {
		printf("listen error\n");
		return -1;
	}

	for(;;) {
		printf("main accept start\n");
		int fd = accept(sock, NULL, NULL);
		if(fd < 0) {
			printf("accept error\n");
			return -1;
		}
		printf("main accept fd:%d\n", fd);

		pid_t pid;
		pid = fork();
		if(pid == 0) {
			char buff[100];
			printf("child read start\n");
			int n = read(fd, &buff, 100);
			printf("child read end\n");
			if(n > 0) {
				write(fd, buff, n);
			}
			printf("child close fd:%d\n", fd);
			close(fd);
			exit(0);
		} else {
			printf("child:%d\n", pid);
		}
	}

	waitpid(-1, NULL, 0);

	return 0;
}
