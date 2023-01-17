#include <iostream>
#include "bitvector.h"

const size_t MAX_SIZE = 70;
const size_t bits_in_one_byte = 8;

std::ostream& operator<<(std::ostream& out, const BitVector& object) {
	if (object.table) {
		for (unsigned i = 0; i < object.size; ++i) {
			out << object.table[i] << ' ';
		}
	}
	return out;
}

std::istream& operator>>(std::istream& in, BitVector& object) {
	std::cout << "Enter the size. ";
	in >> object.size;
	std::cout << "Enter " << object.size << " elements. ";
	for (unsigned i = 0; i < object.size; ++i) {
		in >> object.table[i];
	}
	return in;
}

BitVector::BitVector() 
	: table{ nullptr }
	, size{ 0 }
	, max_size{ MAX_SIZE }
{
	allocate_and_initialize();
}

BitVector::BitVector(const unsigned* new_buff, const size_t& new_size)
	: size { new_size }
	, max_size{ (size > MAX_SIZE) ? size : MAX_SIZE }
	, table { nullptr }
{
	allocate_and_initialize(new_buff);
}

BitVector::BitVector(const BitVector& object) 
	: max_size { object.max_size }
	, size { object.size }
	, table{ nullptr }
{
	allocate_and_initialize(object.table);
}

BitVector::~BitVector() {
	deallocate();
}

size_t BitVector::get_size() const {
	return size;
}

void BitVector::set_size(const size_t new_size) {
	size = new_size;
}

void BitVector::set(const size_t& position, const bool& value) {
	if (table) {
		if (position < 0 || position >= sizeof(unsigned) * bits_in_one_byte * size) {
			std::cout << "The position is out of range!" << std::endl;
			return;
		}
		int index = position / (sizeof(unsigned) * bits_in_one_byte);
		int count = sizeof(unsigned) * bits_in_one_byte - position % (sizeof(unsigned) * bits_in_one_byte) - 1;
		if (value == true) {
			table[index] |= (1 << count);
		}
		else {
			table[index] ^= (1 << count);
		}
	}
	else {
		std::cout << "There is no table." << std::endl;
	}
}

bool BitVector::get(const size_t& position) {
	if (table) {
		if (position < 0 || position >= sizeof(unsigned) * bits_in_one_byte * size) {
			std::cout << "The position is out of range!" << std::endl;
			return false;
		}
		int index = position / (sizeof(unsigned) * bits_in_one_byte);
		int count = sizeof(unsigned) * bits_in_one_byte - position % (sizeof(unsigned) * bits_in_one_byte) - 1;
		return (table[index] & (1 << count)) >> count;
	}
	else {
		std::cout << "There is no table." << std::endl;
	}
}

void BitVector::allocate_and_initialize(const unsigned* new_buff) {
	table = new unsigned[max_size] {};
	if (new_buff) {
		for (unsigned i = 0; i < size; ++i) {
			table[i] = new_buff[i];
		}
	}
}

void BitVector::deallocate() {
	delete[] table;
}