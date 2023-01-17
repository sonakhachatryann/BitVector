#include <iostream>
#include "bitvector.h"

int main() {
	BitVector b1;
	std::cin >> b1;
	std::cout << b1 << std::endl;;
	const size_t size = 6;
	unsigned arr[size] {1, 2, 3, 4, 5, 6};
	BitVector b2(arr, size);
	std::cout << b2 << std::endl;
	b2.set(95, 0);
	std::cout << b2 << std::endl;
	std::cout << b2.get(125);
	return 0;
}