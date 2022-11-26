#include "BigIntCpp.h"
#include <iostream>
#include <string>

int main() {
	std::string hex = "FFFF";
	std::string hex2;
	std::cout << "enter 2 hex strings:" << std::endl;
    //std::cin >> hex;
	std::cin >> hex2;
	BigInteger lhs(hex);
	BigInteger rhs(hex2);
	BigInteger prod;
	prod = lhs*rhs;
	std::cout << lhs.to_string() << std::endl;
	std::cout << rhs.to_string() << std::endl;
    std::cout << prod.to_string() << std::endl;
	return 0;
}
