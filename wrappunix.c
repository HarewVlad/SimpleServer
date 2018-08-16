#include "../unp.h"

void err_sys(const char *x)
{
	perror(x);
	exit(1);
}

void err_quit(const char *msg)
{
	printf("%s", msg);
	exit(1);
}

int Accept(int fd, struct sockaddr *sa, int flags)
{
	int n;
	if ((n = accept(fd, sa, &flags)) < 0)
		err_sys("accept error");
	return n;
}

int Connect(int fd, struct sockaddr *sa, size_t size)
{
	int n;
	if ((n = connect(fd, sa, size)) < 0)
		err_sys("connect error");
	return n;
}

void Close(int fd)
{
	if (close(fd) == -1)
		err_sys("close error");
}

int Socket(int family, int type, int protocol)
{
	int n;
	if ((n = socket(family, type, protocol)) < 0)
	{
		err_sys("socket error");
	}
	return n;
}

void Write(int fd, void *ptr, size_t nbytes)
{
	if (write(fd, ptr, nbytes) != nbytes)
		err_sys("write error");
}

/*void Pthread_mutex_lock(pthread_mutex_lock *mptr)
{
	int n;
	if ((n = pthread_mutex_lock(mptr)) == 0)
		return;

	errno = n;
	err_sys("pthread_mutex_lock error");
}
*/

int Bind(int sockfd, const struct sockaddr *addr,
                socklen_t addrlen)
{
	int n;
	if ((n = bind(sockfd, addr, addrlen)) < 0)
		err_sys("bind error");
	return n;
}

int Listen(int sockfd, int backlog)
{
	int n;
	if ((n = listen(sockfd, backlog)) < 0)
		err_sys("listen error");
	return n;
}