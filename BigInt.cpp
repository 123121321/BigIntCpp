#include "BigIntCpp.h"
#define MAX(X, Y) { X > Y ? X : Y }
#define DEBUG 0
#if DEBUG == 1
#   include <iostream>
#   define LOG(X) { std::cout << "debug(" << X << ")" << std::endl; }
#else
#   define LOG(X) {}
#endif // DEBUG
uint8_t hexDigitValue(const char digit) {
	if (48 <= digit && digit <= 57) {
		return digit - 48;
	}
	else {
		return digit - 65 + 10;
	}
}

char intDigitToHex(const uint8_t digit) {
	if (0 <= digit && digit <= 9) {
		return (char)(digit + 48);
	}
	else {
		return (char)(digit + 65 - 10);
	}
}

BigInteger::BigInteger(std::string hex_str) {
	uint8_t temp = 0;
	for (uint8_t i = 0; i < hex_str.size(); i += 2) {
		temp = 0;
		temp += (hexDigitValue(hex_str[i]) << 4);
		temp += hexDigitValue(hex_str[i + 1]);
		digits.push_back(temp);
	}
}
// convert to a hex string because converting directly
// to a decimal string is a pain
std::string BigInteger::to_string() {
	std::string hex_string;
	uint8_t temp = 0;
	uint8_t hex = 0;
	for (uint16_t i = 0; i < digits.size(); i++) {
		temp = digits[i];
		hex = 0;
		while (temp > 15) {
			temp -= 16;
			hex++;
		}
		hex_string.push_back(intDigitToHex(hex));
		hex = 0;
		while (temp > 0) {
            temp--;
			hex++;
		}
		hex_string.push_back(intDigitToHex(hex));
	}
	return hex_string;
}

// TODO implement cases of differing signs eg
// adding bigInts with a sign of -1 and 1,
// subtracting a bigInt with a sign of -1,
// or maybe do away with them entirely and work
// solely with absolute values because who needs
// anything but the natural numbers

BigInteger BigInteger::operator+(BigInteger &rhs){
    BigInteger sum;
    uint16_t hold;
    uint8_t temp, bound, lBound, rBound, carry;
    carry = 0;
    bound = MAX(digits.size(), rhs.digits.size());
    lBound = digits.size();
    rBound = rhs.digits.size();
    for (uint8_t i = 1; i <= bound; ++i){
        hold = 0;
        if (carry > 0){
            ++hold;
        }
        carry = 0;
        if (lBound >= i){
            hold += digits[lBound - i];
        }
        if (rBound >= i){
            hold += rhs.digits[rBound - i];
        }
        if (hold >= 256){
            ++carry;
            temp = hold - 256;
        } else {
            temp = hold;
        }
        sum.digits.insert(sum.digits.begin(), temp);
    }
    if (carry > 0){
        // note to self, 40ish minutes spent debugging
        // because i used digits.begin instead of
        // sum.digits. ALWAYS check which
        // object's members you are accessing
        sum.digits.insert(sum.digits.begin(), 1);
    }
    return sum;
}

BigInteger operator*(BigInteger &lhs, BigInteger &rhs){
    if (lhs.digits.size() < rhs.digits.size()){
        // to reduce the number of bigint constructions
        // not sure if this actually results in any
        // meaningful performance improvement but
        return (rhs * lhs);
    }
    BigInteger product;
    BigInteger *w_big_int = nullptr;
    std::vector<uint8_t> *w_ints = nullptr;
    std::vector<BigInteger> w_sums;
    uint16_t hold = 0;
    uint8_t carry = 0;
    uint8_t w_prod = 0;
    uint8_t r_bound = rhs.digits.size();
    uint8_t l_bound = lhs.digits.size();
    for (uint8_t i = 1; i <= r_bound; i++){
            w_sums.emplace_back(BigInteger());
            w_big_int = &w_sums[i - 1];
            w_ints = &(w_big_int->digits);
            w_ints->insert(w_ints->begin(), i - 1, 0);
            hold = carry = 0;
            for (uint8_t j = l_bound; j >= 1; j--){
                hold += carry;
                carry = 0;
                hold += rhs.digits[r_bound - i] * lhs.digits[j - 1];
                carry = hold/256;
                w_prod = hold - carry*256;
                w_ints->insert(w_ints->begin(), w_prod);
                hold = 0;
            }
            if (carry > 0){
                w_ints->insert(w_ints->begin(), carry);
            }
    }
    // now add all the partial products together
    // to get the final product
    for (uint8_t k = 0; k < w_sums.size(); k++ ){
        product = product + w_sums[k];
    }
    return product;
}
// TO FINISH
BigInteger BigInteger::operator-(BigInteger &rhs) {
    BigInteger sum;
    if (digits.size() < rhs.digits.size()){
    } else if (digits.size() == rhs.digits.size() && digits[0] ){
        // TO FINISH
    }
    return sum;
}
