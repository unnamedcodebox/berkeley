/** @file
 * @brief     Client declaration
 *
 * @ingroup   Berkeley
 *
 * @copyright (C) 2019
 */

#include <string.h>
#include <bits/types/FILE.h>

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
    void process(FILE *fp, int descriptor);

private:

    unsigned int m_port;
};

} // berkeley
