#include "Client.h"

#include <memory>
#include <cstring>

namespace
{
using namespace berkeley;

constexpr auto DEFAULT_PORT = 9997;
constexpr auto LOCALHOST = "127.0.0.1";
constexpr auto UDP = "udp";

std::shared_ptr<Client>
createClient(std::string address, int port, ProtocolType type = ProtocolType::TCP)
{
    return std::make_shared<Client>(LOCALHOST, port, type);
}

} // anonymous

int main(int argc, char *argv[])
{
    std::shared_ptr<Client> client;

    if(argc > 1 && (!strcmp(argv[1], UDP)))
    {
        client = createClient(LOCALHOST, DEFAULT_PORT, ProtocolType::UDP);
    }
    else {
        client = createClient(LOCALHOST, DEFAULT_PORT);
    }
    client->init();
}
