/** @file
 * @brief     Socket declaration
 *
 * @ingroup   Berkeley
 *
 * @copyright (C) 2019
 */

#pragma once

namespace berkeley
{

/**
 * Class describes Socket
 */
class Socket{

public:

    Socket(unsigned int port);

private:

    int m_descriptor;
};

} // berkeley
