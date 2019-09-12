/** @file
 * @brief     Storage declaration
 *
 * @ingroup   Berkeley
 *
 * @copyright (C) 2019
 */

#pragma once

#include <string>
#include <vector>

namespace berkeley
{

class Storage
{
public:
    explicit Storage(const std::string& message);
    Storage() = default;

    /**
     * Parse message and save numbers to storage
     */
    void prepareStorage();

    /**
     * Sort storage
     */
    std::string toSortedString();

    /**
     * Returns maximum value from storage
     */
    int maxValue();

    /**
     * Returns minimum value from storage
     */
    int minValue();

    /**
     * Returns sum of storage elements
     */
    int sum();

    /**
     * Print storage to string
     */
    std::string toString();

private:
    std::string m_message;
    std::vector<int> m_storage;
    int m_sum;

};

} // berkeley
