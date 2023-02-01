#include <iostream>
#include "bitvector.h"

int main() {

	BitVector b1;
	std::cin >> b1;
	std::cout << b1 << std::endl;
	b1.set(0);
	std::cout << b1.get(64) << std::endl;
	b1.reset(33);
	std::cout << b1 << std::endl;
	BitVector b2(100);
	std::cout << b2.get_size() << std::endl;
	b2.set(4);
	b2.set(65);
	std::cout << b2 << std::endl;
	BitVector b3(b2);
	std::cout << b3 << std::endl;
	std::cout << b3.get_size() << std::endl;

	return 0;
}