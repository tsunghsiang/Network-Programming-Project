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
 * */
void FreeAddrInfo(struct addrinfo *res)
{
	freeaddrinfo(res);
}
