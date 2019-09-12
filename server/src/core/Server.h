/** @file
 * @brief     Server declaration
 *
 * @ingroup   Berkeley
 *
 * @copyright (C) 2019
 */

#pragma once

#include <functional>

namespace berkeley
{

/**
 * Class describes server
 */
class Server{

public:

    explicit Server(unsigned int port);

    /**
     * Initialize server
     */
    void init();

    /**
     * Process the request with special Processor
     */
   template <typename Processor> void process(Processor processor)
    {
        processor();
    }

private:

    unsigned int m_port;
};

} // berkeley
