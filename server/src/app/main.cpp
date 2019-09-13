#include "../core/Server.h"

#include <memory>

namespace
{
using namespace berkeley;

constexpr auto DEFAULT_PORT = 9997;

std::shared_ptr<Server> createServer(int port)
{
    return std::make_shared<Server>(port);
}

} // anonymous

int main(int argc, char *argv[])
{
    auto server = createServer(DEFAULT_PORT);
    server->init();
}
