/** @file
 * @brief     Client declaration
 *
 * @ingroup   Berkeley
 *
 * @copyright (C) 2019
 */

#include "Client.h"


#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <limits>

namespace berkeley
{

namespace
{

constexpr auto LISTENQ = 1024;
constexpr auto SOCKET_ERROR = "SOCKET ERROR";
constexpr auto BIND_ERROR = "BIND ERROR";
constexpr auto LISTEN_ERROR = "LISTEN ERROR";
constexpr auto READLINE_ERROR = "READLINE ERROR";
constexpr auto WRITE_ERROR = "WRITE ERROR";

int socketFileDescriptor(int family, int type, int protocol)
{
    auto descriptor = socket(family, type, protocol);

    if (descriptor < 0)
    {
        std::cerr << SOCKET_ERROR;
    }
    return descriptor;
}

//int attachSocketToPort(
//    int socketFileDescriptor, sockaddr* address, socklen_t length)
//{
//    auto attached = bind(socketFileDescriptor, address, length);

//    if (attached < 0)
//    {
//        std::cerr << BIND_ERROR;
//    }
//    return attached;
//}

//sockaddr_in createSocketAddress(int port)
//{
//    auto address = sockaddr_in();
//    address.sin_family = AF_INET;
//    address.sin_addr.s_addr = INADDR_ANY;
//    address.sin_port = htons(port);

//    return address;
//}

//void listenSocket(int descriptor, int backlog)
//{
//    auto ptr = getenv("LISTENQ");
//    if (ptr != nullptr)
//    {
//        backlog = std::atoi(ptr);
//    }

//    if (listen(descriptor, backlog))
//    {
//        std::cerr << LISTEN_ERROR;
//    }
//}

ssize_t
readline(int fd, void *vptr, ssize_t maxlen)
{
    ssize_t	n, rc;
    char	c, *ptr;

    ptr = static_cast<char*>(vptr);
    for (n = 1; n < maxlen; n++) {
        if ( (rc = read(fd, &c, 1)) == 1) {
            *ptr++ = c;
            if (c == '\n')
                break;
        } else if (rc == 0) {
            if (n == 1)
                return(0);	/* EOF, no data read */
            else
                break;		/* EOF, some data was read */
        } else
            return(-1);	/* error */
    }

    *ptr = 0;
    return(n);
}
/* end readline */

size_t
readMessageFromSocket(int fd, void *ptr, ssize_t maxlen)
{
    auto n = readline(fd, ptr, maxlen);

    if ( n == -1)
    {
        std::cerr << READLINE_ERROR;
    }

    return n;
}

ssize_t						/* Write "n" bytes to a descriptor. */
writen(int fd, const void *vptr, size_t n)
{
    size_t		nleft;
    ssize_t		nwritten;
    const char	*ptr;

    ptr = static_cast<const char*>(vptr);
    nleft = n;
    while (nleft > 0) {
        if ( (nwritten = write(fd, ptr, nleft)) <= 0) {
            if (nwritten < 0 && errno == EINTR)
                nwritten = 0;		/* and call write() again */
            else
                return(-1);			/* error */
        }

        nleft -= nwritten;
        ptr   += nwritten;
    }
    return(n);
}
/* end writen */

void
Writen(int fd, void *ptr, size_t nbytes)
{
    if (writen(fd, ptr, nbytes)
        != static_cast<decltype(writen(fd, ptr, nbytes))>(nbytes))
    {
        std::cerr << BIND_ERROR;
    }
}

void
Inet_pton(int family, const char *strptr, void *addrptr)
{
    int		n;

    if ( (n = inet_pton(family, strptr, addrptr)) < 0)
//        std::cerr("inet_pton error for %s", strptr);	/* errno set */
        std::cerr << "KYRLUK";
    else if (n == 0)
        std::cerr << "KYRLUK";
//        std::cerr("inet_pton error for %s", strptr);	/* errno not set */

    /* nothing to return */
}

} // anonymous

Client::Client(unsigned int port): m_port(port)
{

}

void Client::init()
{
    auto descriptor = socketFileDescriptor(AF_INET, SOCK_STREAM, 0);

    auto serverAddress = sockaddr_in();
    bzero(&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(m_port);

    Inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);

    connect(
        descriptor,
        reinterpret_cast<sockaddr*>(&serverAddress),
        sizeof(serverAddress));

    process(stdin, descriptor);


}

void Client::process(FILE *fp, int descriptor)
{
    char sendLine[65537];
    char recvLine[65537];

    while(fgets(sendLine, 65537, fp) != NULL)
    {
        Writen(descriptor, sendLine, strlen(sendLine));

        if(readMessageFromSocket(descriptor, recvLine, 65537) == 0)
        {
            std::cerr << "MUR MUR MUSYA MUSYA";
        }

        fputs(recvLine, stdout);
    }
}

// anonymous

} // berkeley
