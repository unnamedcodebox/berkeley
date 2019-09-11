/** @file
 * @brief     Client declaration
 *
 * @ingroup   Berkeley
 *
 * @copyright (C) 2019
 */

#include "Client.h"

#include "../halifax/Socket.h"
#include <strings.h>

namespace berkeley
{

namespace
{

auto VALUE = 1;

} // namespace anonymous

Client::Client(unsigned int port) : m_port(port) {}

void Client::init()
{
    auto socket = sockets::socket(AF_INET, SOCK_STREAM, 0);
    auto serverAddress = sockaddr_in();

    // TODO - createSocketAddress function
    bzero(&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(m_port);

    address::toBinary(AF_INET, "127.0.0.1", &serverAddress.sin_addr);

    connect(
        socket,
        sockets_helpers::toSockaddrPointer(&serverAddress),
        sizeof(serverAddress));

    // TODO - Client processor
    process([socket](){return VALUE;});
}

} // namespace berkeley
