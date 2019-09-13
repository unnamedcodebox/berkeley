/** @file
 * @brief     Client declaration
 *
 * @ingroup   Berkeley
 *
 * @copyright (C) 2019
 */

#include "../halifax/Socket.h"

#include <string>

#pragma once

namespace berkeley
{

enum class ProtocolType
{
    TCP,
    UDP
};

/**
 * Class describes client
 */
class Client
{

public:
    Client(
        std::string serverAddress,
        unsigned int port,
        ProtocolType type = ProtocolType::TCP);

    /**
     * Initialize client
     */
    void init();

    /**
     * Process method
     */
    template <typename Processor>
    void process(Processor processor)
    {
        processor();
    }

private:
    std::string m_address;
    unsigned int m_port;
    ProtocolType m_type;
};

} // berkeley
