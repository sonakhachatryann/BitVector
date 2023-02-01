#include <iostream>
#include "bitvector.h"

const size_t MAX_SIZE = 200;
const size_t bits_in_one_byte = 8;

std::ostream& operator<<(std::ostream& out, const BitVector& object) {
	if (object.table) {
		for (unsigned i = 0; i < (object.size - 1) / (sizeof(unsigned) * bits_in_one_byte) + 1; ++i) {
			out << object.table[i] << ' ';
		}
	}
	return out;
}

std::istream& operator>>(std::istream& in, BitVector& object) {
	std::cout << "Enter the size(the number of bits): ";
	in >> object.size;
	std::cout << "Enter " << (object.size - 1) / (sizeof(unsigned) * bits_in_one_byte) + 1 << " elements. ";
	for (unsigned i = 0; i < (object.size - 1) / (sizeof(unsigned) * bits_in_one_byte) + 1; ++i) {
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

BitVector::BitVector(const size_t& count_of_bits) 
	: table{ nullptr }
	, size{ 0 }
	, max_size{ (size > MAX_SIZE) ? size : MAX_SIZE }
{
	set_size(count_of_bits);
	allocate_and_initialize();
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

void BitVector::set_size(const size_t& new_size) {
	size = new_size;
}

void BitVector::set(const size_t& position) {
	if (table) {
		if (!check_position(position)) {
			return;
		}
		int index = position / (sizeof(unsigned) * bits_in_one_byte);
		int count = position % (sizeof(unsigned) * bits_in_one_byte);
		table[index] |= (1 << count);
	}
	else {
		std::cout << "There is no table." << std::endl;
	}
}

void BitVector::reset(const size_t& position) {
	if (table) {
		if (!check_position(position)) {
			return;
		}
		int index = position / (sizeof(unsigned) * bits_in_one_byte);
		int count = position % (sizeof(unsigned) * bits_in_one_byte);
		if (table[index] & (1 << count)) {
			table[index] ^= (1 << count);
		}
	}
	else {
		std::cout << "There is no table." << std::endl;
	}
}

bool BitVector::get(const size_t& position) {
	if (table) {
		if (!check_position(position)) {
			return false;
		}
		int index = position / (sizeof(unsigned) * bits_in_one_byte);
		int count = position % (sizeof(unsigned) * bits_in_one_byte);
		return (table[index] & (1 << count)) >> count;
	}
	else {
		std::cout << "There is no table." << std::endl;
		return false;
	}
}

void BitVector::allocate_and_initialize(const unsigned* new_buff) {
	table = new unsigned[(max_size - 1)/ (sizeof(unsigned) * bits_in_one_byte)+ 1] {};
	if (new_buff) {
		for (unsigned i = 0; i < (size - 1) / (sizeof(unsigned) * bits_in_one_byte) + 1; ++i) {
			table[i] = new_buff[i];
		}
	}
}

void BitVector::deallocate() {
	delete[] table;
}

bool BitVector::check_position(const size_t& position) {
	if (position < 0 || position >= size) {
		std::cout << "The position is out of range!" << std::endl;
		return false;
	}
	return true;
}