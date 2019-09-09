/** @file
 * @brief     Server implementation
 *
 * @ingroup   Berkeley
 *
 * @copyright (C) 2019
 */

#include "Server.h"

#include <iostream>

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <strings.h>

namespace berkeley
{

namespace
{

constexpr auto SOCKET_ERROR = "SOCKET ERROR";
constexpr auto BIND_ERROR = "BIND ERROR";
constexpr auto LISTEN_ERROR = "LISTEN ERROR";

int socketFileDescriptor(int family, int type, int protocol)
{
    auto descriptor = socket(family, type, protocol);

    if (descriptor < 0)
    {
        std::cerr << SOCKET_ERROR;
    }
    return descriptor;
}

int attachSocketToPort(
    int socketFileDescriptor, sockaddr* address, socklen_t length)
{
    auto attached = bind(socketFileDescriptor, address, length);

    if (attached < 0)
    {
        std::cerr << BIND_ERROR;
    }
    return attached;
}

sockaddr_in createSocketAddress(int port)
{
    auto address = sockaddr_in();
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
        backlog = std::atoi(ptr);
    }

    if (listen(descriptor, backlog))
    {
        std::cerr << LISTEN_ERROR;
    }
}

} // anonymous

Server::Server(unsigned int port): m_port(port)
{

}

void Server::init()
{
    auto client = socklen_t();
    pid_t childPid;
    auto descriptor = socketFileDescriptor(AF_INET, SOCK_STREAM, 0);
    auto connectionDescriptor = 0;
    auto clientAddress = sockaddr_in();
    auto serverAddress = createSocketAddress(m_port);
    attachSocketToPort(
        descriptor,
        reinterpret_cast<sockaddr*>(&serverAddress),
        sizeof(serverAddress));
    bzero(&serverAddress, sizeof(serverAddress));
    listenSocket(descriptor, 1024);

    for (;;)
    {
        client = sizeof(clientAddress);
        connectionDescriptor = accept(
            descriptor, reinterpret_cast<sockaddr*>(&clientAddress), &client);
        if (childPid = fork() == 0)
        {
            close(descriptor);
            echo(connectionDescriptor);
            exit(0);
        }
        close(connectionDescriptor);
    }
}

} // berkeley
