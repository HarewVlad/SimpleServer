#include "lib/wrappunix.c"
#include "unp.h"
#include <time.h>

#define MAXLINE 256
#define BACKLOG 10

int main()
{
	int listenfd, connfd, n;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;
	char buff[MAXLINE], IP[16], username[MAXLINE];

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(3333);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	Listen(listenfd, BACKLOG);

	memset(username, 0, sizeof(username));
	for (; ;)
	{
		clilen = sizeof(cliaddr);
		connfd = Accept(listenfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr));

		if ((childpid = fork()) == 0)
		{
			Close(listenfd);

			while (!username[0])
			{
				if ((n = read(connfd, username, MAXLINE)) < 0)
				{
					printf("Error");
				}
			}

			printf("%s entered!\n", username);

			for (; ;)
			{
				if ((n = read(connfd, buff, MAXLINE)) >= 0)
				{
					printf("%s : %s\n", username, buff);

// 					memset(buff, 0, sizeof(buff));
// 					memset(IP, 0, sizeof(IP));
				}
				else
				{
					printf("Error");
				}
			}
		}
	}
}
