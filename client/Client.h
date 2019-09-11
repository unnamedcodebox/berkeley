/** @file
 * @brief     Client declaration
 *
 * @ingroup   Berkeley
 *
 * @copyright (C) 2019
 */

#include <string.h>
#include <bits/types/FILE.h>
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
    int process(FILE *fp, int sock);

private:

    unsigned int m_port;
};

} // berkeley
