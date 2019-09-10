#include "Client.h"

#include <memory>

namespace
{
using namespace berkeley;

constexpr auto DEFAULT_PORT = 9998;

std::shared_ptr<Client> createClient()
{
    return std::make_shared<Client>(DEFAULT_PORT);
}

} // anonymous

int main(int argc, char *argv[])
{
    auto client = createClient();
    client->init();
    return 0;
}
