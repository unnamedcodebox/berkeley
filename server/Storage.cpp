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

//template <typename Number>
//std::string toInfoString(std::string info, Number value)
//{
//    return info + std::to_string(value);
//}

//std::string join(const std::vector<std::string>& parts, char delimiter)
//{
//    auto joined = std::string();

//    for (std::vector<std::string>::const_iterator p = parts.begin();
//         p != parts.end();
//         ++p)
//    {
//        joined += *p;
//        if (p != parts.end() - 1)
//            joined += delimiter;
//    }

//    return joined;
//}

} // anonymous

void Storage::sort()
{
    std::sort(m_storage.begin(), m_storage.end(), std::greater<int>());
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

void Storage::toMessage()
{
//    auto parts = std::vector<std::string>();
//    parts.push_back(toInfoString("Max: ", maxValue()));
//    parts.push_back(toInfoString("Min: ", minValue()));
//    parts.push_back(toInfoString("Sum is:", sum()));
////    auto sortedNumbers = PRINT ARRAY;

//    auto  result = join(parts, '/');
}


} // berkeley
