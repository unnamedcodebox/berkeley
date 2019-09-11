/** @file
 * @brief     Client declaration
 *
 * @ingroup   Berkeley
 *
 * @copyright (C) 2019
 */

#include "../halifax/Socket.h"

#pragma once

namespace berkeley
{

/**
 * Class describes client
 */
class Client
{

public:
    explicit Client(unsigned int port);

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

    unsigned int m_port;
};

} // berkeley
