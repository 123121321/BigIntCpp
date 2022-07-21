#ifndef BIGINTCPP_H
#define BIGINTCPP_H

#include <cstdint>
#include <vector>
#include <string>

class BigInteger {
private:
    std::vector<uint8_t> digits;

public:
    BigInteger(std::string hex_str);

    std::string to_string();

    BigInteger operator+(BigInteger &rhs);
    BigInteger operator-(BigInteger &rhs);
};

#endif
