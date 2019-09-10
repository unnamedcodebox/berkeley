#include "Server.h"

#include <memory>

namespace
{
using namespace berkeley;

constexpr auto DEFAULT_PORT = 9998;

std::shared_ptr<Server> createServer()
{
    return std::make_shared<Server>(DEFAULT_PORT);
}

} // anonymous

int main(int argc, char *argv[])
{
    auto server = createServer();
    server->init();
    return 0;
}
