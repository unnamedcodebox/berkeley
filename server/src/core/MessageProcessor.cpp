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

std::string MessageProcessor::operator()()
{
   return m_storage.toString();
}

} // berkeley
