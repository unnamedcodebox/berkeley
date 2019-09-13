/** @file
 * @brief     Server implementation
 *
 * @ingroup   Berkeley
 *
 * @copyright (C) 2019
 */

#include "Server.h"
#include "../core/MessageProcessor.h"

#include "../../../halifax/Socket.h"

#include <iostream>

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <strings.h>
#include <cstring>
#include <iostream>

namespace berkeley
{

namespace
{

constexpr auto MESSAGE_MAX_LENGTH = 65537;

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

    auto udpSocket = sockets::socket(AF_INET, SOCK_DGRAM, 0);
    sockets::bind(
        udpSocket,
        sockets_helpers::toSockaddrPointer(&serverAddress),
        sizeof(serverAddress));

    fd_set rset;
    FD_ZERO(&rset);
    auto maxfdp = std::max(listenedSocket, udpSocket) + 1;

    FD_SET(listenedSocket, &rset);
    FD_SET(udpSocket, &rset);
    select(maxfdp, &rset, nullptr, nullptr, nullptr);

    if (FD_ISSET(listenedSocket, &rset))
    {
        auto clientLength = static_cast<socklen_t>(sizeof(clientAddress));
        auto connectedSocket = accept(
            listenedSocket,
            sockets_helpers::toSockaddrPointer(&clientAddress),
            &clientLength);

        childPid = fork();

        if (childPid == 0)
        {
            auto processor = [connectedSocket]() {
                char buffer[MESSAGE_MAX_LENGTH];
                while (true)
                {
                    bzero(buffer, sizeof(buffer));
                    auto received = static_cast<ssize_t>(
                        recv(connectedSocket, buffer, MESSAGE_MAX_LENGTH, 0));
                    if (received < 0)
                    {
                        std::cerr << "READ ERROR";
                        break;
                    }
                    auto stringReceived
                        = std::string().append(buffer, strlen(buffer));
                    auto messageProcessor = MessageProcessor(stringReceived);
                    auto processed = std::string("TCP") + " | " + stringReceived
                                     + "\n" + messageProcessor();
                    strcpy(buffer, processed.c_str());

                    if (send(connectedSocket, buffer, processed.length(), 0)
                        != static_cast<int>(processed.length()))
                    {
                        std::cerr << "SEND ERROR: size of sended: "
                                  << sizeof(buffer);
                    };
                }
            };
            close(listenedSocket);
            process(processor);
            exit(0);
        }
        else if (childPid == -1)
        {
            std::cerr << "FORK ERROR";
        }
        close(connectedSocket);
    }
    if (FD_ISSET(udpSocket, &rset))
    {
        char buffer[MESSAGE_MAX_LENGTH];
        while (true)
        {
            auto clientLength = static_cast<socklen_t>(sizeof(clientAddress));
            bzero(buffer, sizeof(buffer));
            auto received = static_cast<ssize_t>(recvfrom(
                udpSocket,
                buffer,
                MESSAGE_MAX_LENGTH,
                0,
                sockets_helpers::toSockaddrPointer(&clientAddress),
                &clientLength));
            if (received < 0)
            {
                std::cerr << "READ ERROR";
                break;
            }
            auto stringReceived = std::string().append(buffer, strlen(buffer));
            auto messageProcessor = MessageProcessor(stringReceived);
            auto processed = std::string("UDP") + " | " + stringReceived + "\n"
                             + messageProcessor();
            strcpy(buffer, processed.c_str());

            sendto(
                udpSocket,
                buffer,
                processed.length(),
                0,
                sockets_helpers::toSockaddrPointer(&clientAddress),
                clientLength);
        }
    }
}

} // namespace berkeley
