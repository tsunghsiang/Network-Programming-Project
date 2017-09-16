/*
 * showip.cpp -- show IP addresses for a host given on the command line
 * */

#include "../header/np.h" 
#include <string.h>
#include <arpa/inet.h> 
#include <netinet/in.h>

int main(int argc, char* argv[])
{
	struct addrinfo hints;
	struct addrinfo * res;
	char ip_str[INET6_ADDRSTRLEN];

	if(argc != 2)
	{
		fprintf(stderr, "usage: ./showip <hostname>\n");
		exit(EXIT_FAILURE);
	}

	// clear address structure
	memset(&hints, 0, sizeof(hints));
	hints.ai_family   = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	
	// reset address information
	NP::GetAddrInfo(argv[1], NULL, &hints, &res);

	printf("IP addresses for %s:\n", argv[1]);

	// loop through all the possible IP addresses
	struct addrinfo * p;
	for(p = res; p != NULL; p = p->ai_next)
	{
		struct sockaddr * addr;
		const char * ip_ver;

		if(p->ai_family == AF_INET)
		{
			addr = p->ai_addr;
		       	inet_ntop(p->ai_family, (struct sockaddr_in *)&addr, ip_str, INET6_ADDRSTRLEN);	
			ip_ver = "IPv4";
		}
		else
		{
			addr = p->ai_addr;
			inet_ntop(p->ai_family, (struct sockaddr_in6 *)&addr, ip_str, INET6_ADDRSTRLEN);
			ip_ver = "IPv6";
		}

		printf("%s %s\n", ip_ver, ip_str);
		// reset string literal array
		memset(ip_str, 0, sizeof(ip_str));
	}

	// free address information 
	NP::FreeAddrInfo(res);

	return 0;
}
