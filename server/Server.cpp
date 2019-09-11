/** @file
 * @brief     Server implementation
 *
 * @ingroup   Berkeley
 *
 * @copyright (C) 2019
 */

#include "Server.h"
#include "../halifax/Socket.h"

#include <iostream>

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <strings.h>
#include <cstring>

namespace berkeley
{

namespace
{

// auto MESSAGE_MAX_LENGTH = 65537;

} // namespace

Server::Server(unsigned int port) : m_port(port) {}

void Server::init()
{
    auto LISTENQ = 5;
    pid_t childPid;

    auto listenedSocket = sockets::socket(AF_INET, SOCK_STREAM, 0);

    auto clientAddress = sockaddr_in();
    auto serverAddress = sockets_helpers::createSocketAddress(m_port);

    sockets::bind(
        listenedSocket,
        sockets_helpers::toSockaddrPointer(&serverAddress),
        sizeof(serverAddress));

    sockets::listen(listenedSocket, LISTENQ);

    for (;;)
    {
        auto clientLength = static_cast<socklen_t>(sizeof(clientAddress));
        auto connectedSocket = accept(
            listenedSocket,
            sockets_helpers::toSockaddrPointer(&clientAddress),
            &clientLength);

        childPid = fork();

        if (childPid == -1)
        {
            std::cerr << "FORK ERROR";
        }
        else
        {
            auto buff = new char[65537];
            close(listenedSocket);

            auto processor = [connectedSocket, buff]()
            {
                while (true)
                {
                    if (recv(connectedSocket, buff, sizeof(buff), 0) <= 0)
                    {
                        return;
                    }
                    std::cout << "Received: " << buff;
                    send(connectedSocket, buff, sizeof(buff), 0);
                }
            };

            process(connectedSocket, processor);
            delete[] buff;
        }
        close(connectedSocket);
    }
}

} // namespace berkeley
