#include "utility.h"

int Utility::isPowerOfTwo(unsigned int x) {
    //return ((x != 0) && !(x & (x - 1)));
    return ((x != 0) && ((x & (~x + 1)) == x));
}

std::string Utility::binary(int number) {
    int remainder;

    if (number <= 1) {
        return std::to_string(number);
    }

    remainder = number % 2;
    return binary(number >> 1) + std::to_string(remainder);
}

std::string Utility::padTo(std::string str, const size_t num, const char paddingChar) {
    if (num > str.size())
        str.insert(0, num - str.size(), paddingChar);
    return str;
}

int Utility::countSubstring(const std::string& str, const std::string& sub) {
    if (sub.length() == 0) return 0;
    int count = 0;
    for (size_t offset = str.find(sub); offset != std::string::npos;
            offset = str.find(sub, offset + sub.length())) {
        ++count;
    }
    return count;
}
