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
#include <netinet/in.h>

namespace berkeley
{

namespace
{

constexpr auto SOCKET_ERROR = "SOCKET ERROR";
constexpr auto BIND_ERROR = "BIND ERROR";
constexpr auto LISTEN_ERROR = "LISTEN ERROR";

int socketFileDescriptor(int family, int type, int protocol)
{
    auto code = socket(family, type, protocol);

    if (code < 0)
    {
        std::cerr << SOCKET_ERROR;
    }
    return code;
}

int attachSocketToPort(
    int socketFileDescriptor, struct sockaddr* address, socklen_t length)
{
    auto attached = bind(socketFileDescriptor, address, length);

    if (attached < 0)
    {
        std::cerr << BIND_ERROR;
    }
    return attached;
}

auto createSocketAddress(int port)
{
    auto address = sockaddr_in();
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    return address;
}

} // anonymous

Server::Server(unsigned int port): m_port(port)
{

}

void Server::init()
{
    auto descriptor = socketFileDescriptor(AF_INET, SOCK_STREAM, 0);
    auto address = createSocketAddress(m_port);
}

} // berkeley
