/** @file
 * @brief     Message processor declaration
 *
 * @ingroup   Berkeley
 *
 * @copyright (C) 2019
 */

#pragma once

#include <string>
#include <vector>

#include "Storage.h"

namespace berkeley
{

class MessageProcessor
{
public:
    explicit MessageProcessor(std::string message);
    std::string operator()();

private:
    Storage m_storage;
};

} // namespace berkley
