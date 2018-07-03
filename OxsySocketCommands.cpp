#include "OxsyLibrary.h"
#include "OxsySocketCommands.h"
#include "OxsyClassPointers.h"

#ifndef WIN32 // _LINUX
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#endif


COxsySocketCommands::COxsySocketCommands(COxsyClassPointers *pClassPointers)
{
	m_pClassPointers = pClassPointers;
}


COxsySocketCommands::~COxsySocketCommands()
{

}


bool COxsySocketCommands::wait_message(Socket *sock, char *buf, int size)
{
	if (sock == NULL) return false;
	if (sock->socketfd == SOCKET_ERROR) return false;

	timeval tv;
	fd_set readfds;
	tv.tv_sec = 0;
	tv.tv_usec = 100000; // 100 milisecunde

	FD_ZERO(&readfds);
    FD_SET((unsigned int)sock->socketfd, &readfds);

	for (int i = 0; i < 10; i++)
	{
		if (select(sock->socketfd + 1, &readfds, NULL, NULL, &tv))
		{
			return receive_message(sock, buf, size);
		}
	}
	
	return false;
}


Socket COxsySocketCommands::init_connection(char *host, int port)
{
	Socket sock;
	sock.socketfd = SOCKET_ERROR;

	struct hostent *host_ent;
	struct in_addr *addr_ptr;
	struct sockaddr_in cli_addr;
	int	sockfd;

//	winsock initialization

	#ifdef WIN32

		WORD wVersionRequested;
		WSADATA wsaData;
		wVersionRequested = MAKEWORD(2, 2);

		if ( WSAStartup( wVersionRequested, &wsaData ) != 0 )
		{
			printf("WSAStartup error.\n");
			return sock;
		}

		if ( LOBYTE( wsaData.wVersion ) != 2 || HIBYTE( wsaData.wVersion ) != 2 )
		{
			WSACleanup();
			printf("wsaData.wVersion error.\n");
			return sock; 
		}

	#endif
	
	if (inet_addr(host) == INADDR_NONE)
	{
		if ((host_ent = (struct hostent *)gethostbyname(host)) == NULL)
		{
			printf("It is not a numeric address.\n");
			return sock;
		}
		else
		{
			addr_ptr = (struct in_addr *) *host_ent->h_addr_list;
			host = inet_ntoa(*addr_ptr);
		}
	}
	
	#ifndef WIN32 // _LINUX
		sigset_t sigmask;
		sigemptyset(&sigmask);
		sigaddset(&sigmask, SIGIO);      
		sigprocmask(SIG_BLOCK, &sigmask, NULL);
	#endif	

//	Open UDP socket.
	 
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		printf("Can't open socket.\n");
		return sock;
	}
	
//	Set the socket to be nonblocking.

	#ifdef WIN32

		unsigned long argp = 1; 
		if (ioctlsocket(sockfd, FIONBIO, &argp) < 0)
		{
			WSACleanup();
			printf("Can't ioctl on socket.\n");
			return sock;
		}

	#else // _LINUX

//		fcntl(sockfd, F_SETFL, O_NONBLOCK | O_ASYNC);
//		fcntl(sockfd, F_SETOWN, getpid());
		
 		if (fcntl(sockfd, F_SETOWN, getpid()) < 0)
		{
			printf("Can't set own socket.\n");
			return sock;
		}

//		fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFL, 0) | O_NONBLOCK | FASYNC);
		
		int val = fcntl(sockfd, F_GETFL, 0);

//		was "defined NewsOS || defined IRIX"
		#if 1
		val |= O_NDELAY;
		#else
		val |= O_NONBLOCK;
		#endif
		val |= FASYNC;
		fcntl(sockfd, F_SETFL, val);
		
	#endif

//	Bind any local address.
	 
	memset((char *) &cli_addr,0,sizeof(cli_addr));
	cli_addr.sin_family = AF_INET;
	cli_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	cli_addr.sin_port = htons(0);

	if (bind(sockfd, (struct sockaddr *) &cli_addr, sizeof(cli_addr)) < 0)
	{
		printf("Can't bind local address.\n");
		return sock;
	}
    
//	Fill in the structure with the address of the server.

	sock.socketfd = sockfd;
	
	memset((char *) &sock.serv_addr,0, sizeof(sock.serv_addr));
	sock.serv_addr.sin_family = AF_INET;
	sock.serv_addr.sin_addr.s_addr = inet_addr(host);
	sock.serv_addr.sin_port = htons((unsigned short)port);
	
	return sock;
}


bool COxsySocketCommands::send_message(Socket *sock, char *buf)
{
	int n = strlen(buf) + 1; // count and send it with '\0' character.

	return (sendto(sock->socketfd, buf, n, 0, (struct sockaddr *)&sock->serv_addr,
			sizeof(sock->serv_addr)) == n) ? true : false;
}
	   

bool COxsySocketCommands::receive_message(Socket *sock, char *buf, int size)
{
	if (sock == NULL) return false;
	if (sock->socketfd == SOCKET_ERROR) return false;
	if (buf == NULL) return false;

	struct sockaddr_in serv_addr;
    
	int servlen = sizeof(serv_addr);

	#ifdef WIN32
		int n = recvfrom(sock->socketfd, buf, size, 0, (struct sockaddr *)&serv_addr, &servlen);
	#else // _LINUX
		int n = recvfrom(sock->socketfd, buf, size, 0, (struct sockaddr *)&serv_addr, (socklen_t *)&servlen);
	#endif
	
	if (n < 0)
	{
		#ifdef WIN32
			if (n == WSAETIMEDOUT) return false;
			if (n == -1 && errno == WSAEWOULDBLOCK) return false;
		#else // _LINUX
			if (n == -1 && errno == EWOULDBLOCK) return false;
		#endif
			else
			{
				fflush(stderr);
				return false;
			}
	}
	else
	{
		buf[n] = '\0' ;
		sock->serv_addr.sin_port = serv_addr.sin_port;
		return (n > 0) ? true : false;
	}
}


void COxsySocketCommands::close_connection(Socket *sock)
{
	if (sock == NULL) return;
	if (sock->socketfd == SOCKET_ERROR) return;

	#ifdef WIN32
		shutdown(sock->socketfd, SD_BOTH);
		closesocket(sock->socketfd);
	#else // _LINUX
		close(sock->socketfd);
	#endif
}
