/** @file
 * @brief     Storage implementation
 *
 * @ingroup   Berkeley
 *
 * @copyright (C) 2019
 */

#include "Storage.h"

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>

namespace berkeley
{

namespace {

std::string toInfoString(std::string info, int value)
{
    return info + std::to_string(value);
}

std::string toInfoString(std::string info, std::string value)
{
    return info + value;
}

} // anonymous

Storage::Storage(const std::string& message): m_message(message)
{
    prepareStorage();
}

void Storage::prepareStorage()
{
    std::for_each(
        m_message.begin(), m_message.end(), [this](const auto& element) {
            if (std::isdigit(element))
            {
                auto number = std::atoi(&element);
                if (number >= 0 && number <= 9)
                {
                    m_storage.push_back(number);
                }
            }
        });
}

std::string Storage::toSortedString()
{
    std::sort(m_storage.begin(), m_storage.end(), std::greater<int>());

    // Not elegant solution (Boost::join or Qt's join is good for this)
    return std::accumulate(std::next(m_storage.begin()),m_storage.end(),
        std::to_string(*m_storage.begin()),
        [](const auto& lhs, const auto& rhs)
    {
        return lhs + " " + std::to_string(rhs);
    });
}

int Storage::maxValue()
{
    return *std::max_element(m_storage.begin(), m_storage.end());
}

int Storage::minValue()
{
    return *std::min_element(m_storage.begin(), m_storage.end());
}

int Storage::sum()
{
    m_sum = std::accumulate(m_storage.begin(), m_storage.end(), 0);
    return m_sum;
}

std::string Storage::toString()
{
    if (!m_storage.empty())
    {
        auto parts = std::vector<std::string>();
        parts.push_back(toInfoString("Max: ", maxValue()));
        parts.push_back(toInfoString("Min: ", minValue()));
        parts.push_back(toInfoString("Sum is: ", sum()));
        parts.push_back(toInfoString("Sorted is: ", toSortedString()));

        // Another one "join" problem
        auto join = std::accumulate(
            std::next(parts.begin()),
            parts.end(),
            std::string(*parts.begin()),
            [](const auto& lhs, const auto& rhs) { return lhs + " / " + rhs; });

        return "[Message info]: [" + join + "]";
    }

    return {};
}

} // berkeley
