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

#endif
