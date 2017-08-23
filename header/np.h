/*
 * np.h -- define function prototypes for helper functions
 * */
#ifndef NP_H
#define NP_H

#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>

/*
 * DNS lookup / service name lookup :
 * node: the hostname to connect to / IP address
 * service: port  number / service name (ex: http, ftp, etc) 
 * hints: the address information that you've filled out with relevant information
 * */
int GetAddrInfo(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res);

/*
 * Free one or more addrinfo structures returned by getaddrinfo(),
 * res: a linked list that contains a list of addrinfo structure
 * */
void FreeAddrInfo(struct addrinfo *res);

/*
 * creates an endpoint for communication/IO and returns a file descriptor that refers to that endpoint.
 * domain: a communication domain
 * type: the indicated type, which specifies the communication semantics
 * protocol: specifies a particular protocol to be used with the socket.  
 *           Normally only a single protocol exists to support a particular 
 *           socket type within a given protocol family 
 * */
int Socket(int domain, int type, int protocol);

/*
 * Bind a name to a socket. 
 * bind() assigns the address specified by 'addr' to the socket referred to by the file descriptor 'sockfd'.
 * sockfd: socket file descriptor returned from socket()
 * my_addr: the address information that is to be bound to socket descriptor (IP / port number)
 * addrlen: size of my_addr
 * */
int Bind(int sockfd, struct sockaddr *my_addr, int addrlen);

/*
 * Set socket options
 * The SetSocketOptions() function provides an application program with the means to control socket behavior. 
 * An application program can use SetSocketOptions() to allocate buffer space, control timeouts, or permit 
 * socket data broadcasts. To see more details, please check linux man page
 * */
int SetSocketOptions(int socket, int level, int option_name, const void *option_value, socklen_t option_len);

/*
 * Make a connection on a socket to the address specified by parameter 'address'
 * socket: local socket file descriptor
 * address: structure containing the peer address. The length and format of the 
 *          address depend on the address family of the socket
 * address_len: length of address
 */
int Connect(int socket, const struct sockaddr *address, socklen_t address_len);

/*
 * Listen for connections on a socket - socket that will be used to accept connection requests 
 * sockfd: socket file descriptor of host waiting to be connected
 * backlog: the maximum connection pending in the queue
 * Note: the socket refers to type SOCK_STREAM or SOCK_SEQPACKET (connection-based).
 */ 
int Listen(int sockfd, int backlog);

/*
 * Accept a connection on a socket - It extracts the first connection request on the queue of 
 * pending connections for the listening socket
 * sockfd: socket number return from socket() used by host for incoming connections
 * addr: the address structure to be filled in with peer address whose type is determined by
 *       address family (AF_INET or AF_INET6)
 * addrlen: size of addr
 * */
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

#endif
