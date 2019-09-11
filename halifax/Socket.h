/** @file
 * @brief     Socket declaration
 *
 * @ingroup   Berkeley
 *
 * @copyright (C) 2019
 */

#pragma once

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

namespace berkeley
{

/**
 * Wrappers around berkeley sockets functions
 */
namespace sockets
{

/**
 * Returns socket descriptor
 */
int socket(int family, int type, int protocol);

/**
 * Bind socket to local protocol address
 */
int bind(int socket, sockaddr* address, socklen_t length);

/**
 * Listen socket
 */
void listen(int socket, int backlog);

/**
 * Connect client to server
 */
void connect(
    int socket, const struct sockaddr* serverAddress, socklen_t addressLength);

/**
 * Returns connected socket
 */
int accept(
    int listeningSocket, sockaddr* clientAddress, socklen_t* addressLength);

} // namespace sockets

namespace sockets_helpers
{

sockaddr* toSockaddrPointer(sockaddr_in* addr);

/**
 * Create socket address
 */
sockaddr_in createSocketAddress(int port);

} // namespace sockets_helpers

namespace address
{

void toBinary(int family, const char* string, void* address);

} // namespace addresses

} // namespace berkeley
