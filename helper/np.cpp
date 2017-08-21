/*
 * The header file defines prototypes of helper functions that assist us simplify
 * network progrmming sophistications
 * */

#include "../header/np.h"

/*
 * DNS lookup / service name lookup :
 * node: the hostname to connect to / IP address
 * service: port  number / service name (ex: http, ftp, etc)
 * hints: the address information that you've filled out with relevant information
 * */
 int GetAddrInfo(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res)
{
	int status;
	if ((status = getaddrinfo(node, service, hints, res)) != 0) 
	{    
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));    
		exit(EXIT_FAILURE);
       	}
	return status;
}

/*
 * Free one or more addrinfo structures returned by getaddrinfo(),
 * res: a linked list that contains a list of addrinfo structure
 * */
void FreeAddrInfo(struct addrinfo *res)
{
	freeaddrinfo(res);
}

/*
 * creates an endpoint for communication/IO and returns a file descriptor that refers to that endpoint.
 * type: the indicated type, which specifies the communication semantics
 * protocol: specifies a particular protocol to be used with the socket.
 *	     Normally only a single protocol exists to support a particular
 *           socket type within a given protocol family
 *
 * */
int Socket(int domain, int type, int protocol)
{
	int fd; // file descriptor
	if((fd = socket(domain, type, protocol)) == -1)
	{
		fprintf(stderr, "socket error");
		exit(EXIT_FAILURE);
	}
	return fd;
}

/*
 * Bind a name to a socket.
 * bind() assigns the address specified by 'addr' to the socket referred to by the file descriptor 'sockfd'.
 * sockfd: socket file descriptor returned from socket()
 * my_addr: the address information that is to be bound to socket descriptor (IP / port number)
 * addrlen: size of my_addr
 * */
int Bind(int sockfd, struct sockaddr *my_addr, int addrlen)
{
	int status;
	if((status = bind(sockfd, my_addr, addrlen) == -1))
	{
                fprintf(stderr, "binding error");
                exit(EXIT_FAILURE);
	}
	return status;
}

