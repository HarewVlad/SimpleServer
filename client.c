#include "lib/wrappunix.c"
#include "unp.h"
#include <time.h>

#define MAXLINE 256

int main(int argc, char **argv)
{
	int sockfd, n;
	char buff[MAXLINE], username[MAXLINE];
	struct sockaddr_in servaddr;

	if (argc != 2)
		return 1;

	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(3333);

	if ((inet_pton(AF_INET, argv[1], &servaddr.sin_addr)) <= 0)
	{
		err_quit("Goddamn");
	}

	Connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	memset(username, 0, sizeof(username));
	printf("Enter username : ");
	scanf("%s", username);
	n = write(sockfd, username, MAXLINE);

	if (n < 0)
	{
		err_quit("Goddamn");
	}

	for (; ;)
	{
		scanf("%s", buff);

		n = write(sockfd, buff, MAXLINE);

		if (n < 0)
		{
			err_quit("Goddamn");
		}

		memset(buff, 0, sizeof(buff));
	}
	
}