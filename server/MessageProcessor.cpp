/** @file
 * @brief     Message processor implementation
 *
 * @ingroup   Berkeley
 *
 * @copyright (C) 2019
 */

#include "MessageProcessor.h"

namespace berkeley
{

MessageProcessor::MessageProcessor(std::string message)
    : m_storage(Storage(message))
{
}

} // berkeley
