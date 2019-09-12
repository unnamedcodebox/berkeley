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
    explicit Storage(std::string message);

    /**
     * Sort storage
     */
    void sort();

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
     * give the
     */
    void toMessage();

private:
    std::string m_message;
    std::vector<int> m_storage;
    int m_sum;

};

} // berkeley
