/** @file
 * @brief     Server declaration
 *
 * @ingroup   Berkeley
 *
 * @copyright (C) 2019
 */

#pragma once

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

private:

    unsigned int m_port;
};

} // berkeley
