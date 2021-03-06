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
#include <unistd.h>


namespace NP
{
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

/*
 * Send a message on a socket - initiate transmission of a message from the specified socket to its peer
 * socket: socket file descriptor
 * buffer: a pointer to the message to be sent
 * length: length of the message to be sent
 * flags: specifies the type of message transmission
 * For more details, please refer to linux man page
 * */
ssize_t Send(int socket, const void *buffer, size_t length, int flags);

/*
 * Receive a message from a connected socket - receive a message from a connection-mode or connectionless-mode socket.
 * socket: socket file descriptor 
 * buffer: a pointer to a buffer where message is filled
 * length: length of message to be filled in the buffer
 * flags: specifies the type of message reception
 * */
ssize_t Recv(int socket, void *buffer, size_t length, int flags);

/*
 * Send a message on a socket - If sendto() is used on a connection-mode (SOCK_STREAM, SOCK_SEQPACKET) socket, the 
 * arguments dest_addr and addrlen are ignored. Otherwise dest_addr should be filled in once message is transmitted
 * on connectionless-mode socket
 * sockfd: socket file descriptor
 * buf: a pointer to a buffer where message is filled
 * len: length of message to be filled in the buffer
 * flags: specifies the type of message transmission
 * dest_addr: destination address information
 * addrlen: length of destination address information
 * */
ssize_t SendTo(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);

/*
 * Receive a message from a socket - receive a message from a connection-mode or connectionless-mode socket. 
 * It is normally used with connectionless-mode sockets because it permits the application to retrieve the 
 * source address of received data.
 * sockfd: socket file descriptor
 * buf: a pointer to a buffer where message is filled
 * len: length of message to be filled in the buffer
 * flags: specifies the type of message transmission
 * from: the address information the message is received from
 * fromlen: size of source address
 * */
ssize_t RecvFrom(int sockfd, void *buf, int len, unsigned int flags, struct sockaddr *from, int *fromlen);

/*
 * Close a file descriptor - deallocate the file descriptor indicated by fd
 * fd: file descriptor
 * */
int Close(int fd);

/*
 * Shut down socket send and receive operations - it does not actually close the file decriptor and just change
 * its usability
 * socket: socket file descriptor whose behavior is going to be changed
 * how: specifies the type of shutdown. The values are as follows:
 *      SHUT_RD     Disables further receive operations.
 *      SHUT_WR     Disables further send operations.
 *      SHUT_RDWR   Disables further send and receive operations.
 * For more details, please refer to linux man page
 * */
int ShutDown(int socket, int how);

/*
 * Tell you who is at the other end of a connected stream socket - retreive the peer address of the specified socket;
 * store the address in the structure pointed to by peer_addr; store the length of this address in the object pointed 
 * to by the addrlen argument.
 * sockfd: socket file descriptor
 * peer_addr: peer address information
 * addrlen: size of peer address
 * */
int GetPeerName(int sockfd, struct sockaddr *peer_addr, int *addrlen);

/*
 * Get the name of the computer where your program is running
 * hostname: a pointer to the buffer where host name is filled
 * size: size of hostname
 * */
int GetHostName(char *hostname, size_t size);

}
#endif
