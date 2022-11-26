#ifndef BIGINTCPP_H
#define BIGINTCPP_H

#include <cstdint>
#include <vector>
#include <string>

class BigInteger {
private:
    std::vector<uint8_t> digits;
    // extra work to fit the convention of pos
    // numbers having a sign of 1, negative of -1,
    // and zero having a sign of 0
    // int8_t sign:2;

public:
    BigInteger() {}
    BigInteger(std::string hex_str);

    std::string to_string();

    BigInteger operator+(BigInteger &rhs);
    friend BigInteger operator*(BigInteger &lhs, BigInteger &rhs);
    BigInteger operator-(BigInteger &rhs);
};

#endif
