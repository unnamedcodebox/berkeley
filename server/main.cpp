#include "Server.h"


#include <memory>
#include <stdio.h>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <iostream>

#include <cstdlib>
#include <cstdio>

#include <strings.h>
namespace
{
using namespace berkeley;

constexpr auto DEFAULT_PORT = 9998;

std::shared_ptr<Server> createServer(int port)
{
    return std::make_shared<Server>(port);
}

} // anonymous

int main(int argc, char *argv[])
{
    auto server = createServer(DEFAULT_PORT);
    server->init();
    return 0;
}

//#include <stdio.h>
//#include <stdlib.h>
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <unistd.h>

//#define BUFFER_SIZE 1024
//#define on_error(...) { fprintf(stderr, __VA_ARGS__); fflush(stderr); exit(1); }

//int main (int argc, char *argv[]) {
////  if (argc < 2) on_error("Usage: %s [port]\n", argv[0]);

//  int port = 9998;

//  int server_fd, client_fd, err;
//  struct sockaddr_in server, client;
//  char buf[BUFFER_SIZE];

//  server_fd = socket(AF_INET, SOCK_STREAM, 0);
//  if (server_fd < 0) on_error("Could not create socket\n");

//  server.sin_family = AF_INET;
//  server.sin_port = htons(port);
//  server.sin_addr.s_addr = htonl(INADDR_ANY);

//  int opt_val = 1;
//  setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof opt_val);

//  err = bind(server_fd, (struct sockaddr *) &server, sizeof(server));
//  if (err < 0) on_error("Could not bind socket\n");

//  err = listen(server_fd, 128);
//  if (err < 0) on_error("Could not listen on socket\n");

//  printf("Server is listening on %d\n", port);

//  while (1) {
//    socklen_t client_len = sizeof(client);
//    client_fd = accept(server_fd, (struct sockaddr *) &client, &client_len);

//    if (client_fd < 0) on_error("Could not establish new connection\n");

//    while (1) {
//      int read = recv(client_fd, buf, BUFFER_SIZE, 0);

//      if (!read) break; // done reading
//      if (read < 0) on_error("Client read failed\n");

//      err = send(client_fd, buf, read, 0);
//      if (err < 0) on_error("Client write failed\n");
//    }
//  }

//  return 0;
//}
