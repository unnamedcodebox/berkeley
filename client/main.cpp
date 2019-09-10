#include "Client.h"

#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

#include <strings.h>
#include <limits>

#include <memory>

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

char *
Fgets(char *ptr, int n, FILE *stream)
{
    char	*rptr;

    if ( (rptr = fgets(ptr, n, stream)) == NULL && ferror(stream))
        std::cerr << ("fgets error");

    return (rptr);
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


namespace
{
//using namespace berkeley;

constexpr auto DEFAULT_PORT = 9998;

//std::shared_ptr<Client> createClient(int port)
//{
//    return std::make_shared<Client>(port);
//}

} // anonymous

int main(int argc, char *argv[])
{
//    auto client = createClient(DEFAULT_PORT);
//    auto avto = client->init();
    auto socket = socketFileDescriptor(AF_INET, SOCK_STREAM, 0);

    auto serverAddress = sockaddr_in();
    bzero(&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(DEFAULT_PORT);
    Inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);

    connect(
        socket,
        reinterpret_cast<sockaddr*>(&serverAddress),
        sizeof(serverAddress));

    char sendLine[65537];
    char recvLine[65537];

    /* Send the word to the server */
    auto received = 0;
    auto length = 5;
//               echolen = strlen(argv[2]);
//               if (send(sock, argv[2], echolen, 0) != echolen) {
//                 Die("Mismatch in number of sent bytes");
//               }
//               /* Receive the word back from the server */
//               fprintf(stdout, "Received: ");
//               while (received < echolen) {
//                 int bytes = 0;
//                 if ((bytes = recv(sock, buffer, BUFFSIZE-1, 0)) < 1) {
//                   Die("Failed to receive bytes from server");
//                 }
//                 received += bytes;
//                 buffer[bytes] = '\0';        /* Assure null terminated string */
//                 fprintf(stdout, buffer);
//               }

//    while(Fgets(sendLine, 65537, stdin) != NULL)
//    {
        write(socket, sendLine, 65537);

//        if(recv(socket, &recvLine, sizeof(sendLine), 0) < 1)
//        {
//            std::cerr << "MUR MUR MUSYA MUSYA";
//        }

//        std::cout << recvLine;
//    }

        int echo
        /* Send the word to the server */
                    echolen = strlen(argv[2]);
                    if (send(sock, argv[2], echolen, 0) != echolen) {
                      Die("Mismatch in number of sent bytes");
                    }
                    /* Receive the word back from the server */
                    fprintf(stdout, "Received: ");
                    while (received < echolen) {
                      int bytes = 0;
                      if ((bytes = recv(sock, buffer, BUFFSIZE-1, 0)) < 1) {
                        Die("Failed to receive bytes from server");
                      }
                      received += bytes;
                      buffer[bytes] = '\0';        /* Assure null terminated string */
                      fprintf(stdout, buffer);
                    }
}
