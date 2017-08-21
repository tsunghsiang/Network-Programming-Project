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

/*
 * DNS lookup / service name lookup :
 * node: the hostname to connect to / IP address
 * service: port  number / service name (ex: http, ftp, etc) 
 * hints: the address information that you've filled out with relevant information
 * */
int GetAddrInfo(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res);

/*
 * Free one or more addrinfo structures returned by getaddrinfo(),
 * */
void FreeAddrInfo(struct addrinfo *res);

#endif
