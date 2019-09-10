/** @file
 * @brief     Server implementation
 *
 * @ingroup   Berkeley
 *
 * @copyright (C) 2019
 */

#include "Server.h"

#include <iostream>
#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <strings.h>

namespace berkeley
{

namespace
{

using SocketAddress  = sockaddr*;
using SocketLength = socklen_t;
using Socket = int;

constexpr auto LISTENQ = 1024;
constexpr auto MESSAGE_MAX_LENGTH = 65537;
constexpr auto SOCKET_ERROR = "SOCKET ERROR";
constexpr auto BIND_ERROR = "BIND ERROR";
constexpr auto LISTEN_ERROR = "LISTEN ERROR";
constexpr auto READLINE_ERROR = "READLINE ERROR";
constexpr auto WRITE_ERROR = "WRITE ERROR";

Socket createSocket(int family, int type, int protocol)
{
    auto socket = ::socket(family, type, protocol);

    if (socket < 0)
    {
        std::cerr << SOCKET_ERROR;
    }
    return socket;
}

int bindSocket(
    int socket, SocketAddress address, SocketLength length)
{
    auto binded = bind(socket, address, length);

    if (binded < 0)
    {
        std::cerr << BIND_ERROR;
    }
    return binded;
}

sockaddr_in createSocketAddress(int port)
{
    auto address = sockaddr_in();
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    return address;
}

void listenSocket(int descriptor, int backlog)
{
    auto ptr = getenv("LISTENQ");
    if (ptr != nullptr)
    {
        backlog = std::stoi(ptr);
    }

    if (listen(descriptor, backlog))
    {
        std::cerr << LISTEN_ERROR;
    }
}

//ssize_t
//readline(int fd, void *vptr, ssize_t maxlen)
//{
//    ssize_t	n, rc;
//    char	c, *ptr;

//    ptr = static_cast<char*>(vptr);
//    for (n = 1; n < maxlen; n++) {
//        if ( (rc = read(fd, &c, 1)) == 1) {
//            *ptr++ = c;
//            if (c == '\n')
//                break;
//        } else if (rc == 0) {
//            if (n == 1)
//                return(0);	/* EOF, no data read */
//            else
//                break;		/* EOF, some data was read */
//        } else
//            return(-1);	/* error */
//    }

//    *ptr = 0;
//    return(n);
//}
///* end readline */

//size_t
//readMessageFromSocket(int fd, void *ptr, ssize_t maxlen)
//{
//    auto n = readline(fd, ptr, maxlen);

//    if ( n == -1)
//    {
//        std::cerr << READLINE_ERROR;
//    }

//    return n;
//}

SocketAddress toSockaddrPointer(sockaddr_in* addr)
{
    return reinterpret_cast<SocketAddress>(addr);
}

} // anonymous

Server::Server(unsigned int port): m_port(port)
{

}

void Server::init()
{
    auto client = socklen_t();
    pid_t childPid;
    auto descriptor = createSocket(AF_INET, SOCK_STREAM, 0);
    auto connectionDescriptor = 0;
    auto clientAddress = sockaddr_in();
    auto serverAddress = createSocketAddress(m_port);
    bindSocket(
        descriptor,
        toSockaddrPointer(&serverAddress),
        sizeof(serverAddress));
    listenSocket(descriptor, LISTENQ);

    while(true)
    {
        client = sizeof(clientAddress);
        connectionDescriptor = accept(
            descriptor, toSockaddrPointer(&clientAddress), &client);
        childPid = fork();

        if (childPid == 0)
        {
            close(descriptor);
            echo(connectionDescriptor);
            exit(0);
        }
        close(connectionDescriptor);
    }
}

void Server::echo(int socketDescriptor)
{

    char line[MESSAGE_MAX_LENGTH];
    auto read = recv(socketDescriptor, &line, MESSAGE_MAX_LENGTH, 0);

    while(true)
    {
        if (read == 0)
        {
            return;
        }
        send(socketDescriptor,line,read, 0);
//         if (error < 0) on_error("Client write failed\n");
    }
}

} // berkeley
