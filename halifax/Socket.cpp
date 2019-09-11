/** @file
 * @brief     Socket implementation
 *
 * @ingroup   Berkeley
 *
 * @copyright (C) 2019
 */

#include "Socket.h"

#include <arpa/inet.h>
#include <iostream>
#include <strings.h>

namespace berkeley
{

namespace
{

constexpr auto SOCKET_ERROR = "SOCKET ERROR";
constexpr auto BIND_ERROR = "BIND ERROR";
constexpr auto LISTEN_ERROR = "LISTEN ERROR";
constexpr auto WRITE_ERROR = "WRITE ERROR";
constexpr auto CONNECT_ERROR = "CONNECT_ERROR";
constexpr auto ACCEPT_ERROR = "ACCEPT_ERROR";

void errorMessage(std::string message)
{
    std::cerr << message;
}

} // namespace

namespace sockets
{

int socket(int family, int type, int protocol)
{
    auto socketDescriptor = ::socket(family, type, protocol);

    if (socketDescriptor < 0)
    {
        errorMessage(SOCKET_ERROR);
    }
    return socketDescriptor;
}

int bind(int socket, sockaddr* address, socklen_t length)
{
    auto binded = ::bind(socket, address, length);

    if (binded < 0)
    {
        errorMessage(BIND_ERROR);
    }
    return binded;
}

void listen(int socket, int backlog)
{
    char* ptr;
    if ((ptr = getenv("LISTENQ")) != NULL)
    {
        backlog = std::stoi(ptr);
    }

    if (::listen(socket, backlog) == 1)
    {
        errorMessage(LISTEN_ERROR);
    }
}

void connect(int socket, const sockaddr* serverAddress, socklen_t addressLength)
{
    if (::connect(socket, serverAddress, addressLength) < 0)
    {
        errorMessage(CONNECT_ERROR);
    }
}

int accept(
    int listeningSocket, sockaddr* clientAddress, socklen_t* addressLength)
{
    auto connectedSocket
        = ::accept(listeningSocket, clientAddress, addressLength);

    if (connectedSocket < 0)
    {
        errorMessage(ACCEPT_ERROR);
    }
    return connectedSocket;
}

} // namespace sockets

namespace sockets_helpers
{

sockaddr_in createSocketAddress(int port)
{
    auto address = sockaddr_in();
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    return address;
}

sockaddr* toSockaddrPointer(sockaddr_in* addr)
{

    return reinterpret_cast<sockaddr*>(addr);
}

} // namespace sockets_helpers

namespace address {

void toBinary(int family, const char* string, void* address)
{
    inet_pton(family, string, address);
}

}

} // namespace berkeley
