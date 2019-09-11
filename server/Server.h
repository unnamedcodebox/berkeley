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
     * Process method
     */
   void process(std::function<void()> processor)
    {
        processor();
    }

private:

    unsigned int m_port;
};

} // berkeley
