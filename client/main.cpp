#include "Client.h"

#include <memory>

namespace
{
using namespace berkeley;

constexpr auto DEFAULT_PORT = 9997;

std::shared_ptr<Client> createClient(int port)
{
    return std::make_shared<Client>(port);
}

} // anonymous

int main(int argc, char *argv[])
{
    auto client = createClient(DEFAULT_PORT);
    client->init();

    return 1;
}
