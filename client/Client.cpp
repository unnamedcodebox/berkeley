/** @file
 * @brief     Client declaration
 *
 * @ingroup   Berkeley
 *
 * @copyright (C) 2019
 */

#include "Client.h"

#include "../halifax/Socket.h"
#include <iostream>
#include <chrono>
#include <strings.h>
#include <cstring>
#include<vector>

#include <memory>

namespace berkeley
{

namespace
{

constexpr auto MESSAGE_MAX_LENGTH = 65537;

auto getTime()
{
    auto moment = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(moment);
    return std::ctime(&time);
}

template <typename T>
void printMessage(const T& message)
{
    std::cout << std::string("From server |:") << getTime()
              << " | length: " << strlen(message) << "): " << message << "\n";
}

} // namespace

Client::Client(unsigned int port) : m_port(port) {}

void Client::init()
{
    auto socket = sockets::socket(AF_INET, SOCK_STREAM, 0);
    auto serverAddress = sockaddr_in();

    // TODO - createSocketAddress function // SocketAddress micro class???
    bzero(&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(m_port);

    address::toBinary(AF_INET, "127.0.0.1", &serverAddress.sin_addr);

    sockets::connect(
        socket,
        sockets_helpers::toSockaddrPointer(&serverAddress),
        sizeof(serverAddress));

     // TODO - Client processor
    auto processor = [socket]()
    {
        char sendBuff[MESSAGE_MAX_LENGTH];
        char replyBuff[MESSAGE_MAX_LENGTH];

        while (true)
        {
            std::cin.getline(sendBuff, 65537);
            // TODO - send and recv wrappers
            auto sended = send(socket, sendBuff, strlen(sendBuff), 0);
            if(sended != (int)strlen(sendBuff))
            {
                std::cerr << "SEND ERROR" << "sended size was: " << sended;
            }
            std::cout << std::string(sendBuff).length();
            bzero(replyBuff, sizeof (replyBuff));
            auto received = static_cast<ssize_t>(recv(socket, replyBuff, 65537, 0));
            std::cout << " // Received from socket: " << received << " // ";
            if (received <= 0)
            {
                break;
            }
            printMessage(replyBuff);
        }
    };

    process(processor);
}

} // namespace berkeley
