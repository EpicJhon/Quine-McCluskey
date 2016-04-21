#ifndef UTILITY_H
#define UTILITY_H

#include "includes.h"

class Utility {
public:
    /**
     * convert a number to its binary representation
     * @param number
     * @return 
     */
    static std::string binary(int number);
    /**
     * Returns count of non-overlapping occurrences of 'sub' in 'str'
     * @param str
     * @param sub
     * @return 
     */
    static int countSubstring(const std::string& str, const std::string& sub);
    static int isPowerOfTwo(unsigned int x);
    static std::string padTo(std::string str, const size_t num, const char paddingChar = '0');

    /**
     * Determines whether the container contains the continent
     * 
     * @param container
     * @param continent
     * @return 
     */
    template<typename _InputIterator1, typename _InputIterator2>
    static bool contains(_InputIterator1 container, _InputIterator2 continent) {
        return std::includes(container.begin(), container.end(), continent.begin(), continent.end());
    };

    /**
     * Check for a needle in a haystack
     * @param haystack
     * @param needle
     * @return 
     */
    template<typename _haystack, typename _Needle>
    static bool exists(_haystack haystack, _Needle needle) {
        return (std::find(haystack.begin(), haystack.end(), needle) != haystack.end());
    };

    /**
     * Remove all the needles in the haystack
     * @param haystack
     * @param needle
     */
    template<typename type>
    static void removeAll(std::vector<type>& haystack, type needle) {
        haystack.erase(std::remove(haystack.begin(), haystack.end(), needle), haystack.end());
    };
};

#endif /* UTILITY_H */

