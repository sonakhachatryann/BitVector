#ifndef BITVECTOR_H
#define BITVECTOR_H

class BitVector {
	friend std::ostream& operator<<(std::ostream&, const BitVector&);
	friend std::istream& operator>>(std::istream&, BitVector&);

public:
	BitVector();
	BitVector(const size_t& count_of_bits);
	BitVector(const BitVector&);
	~BitVector();

	size_t get_size() const;
	void set_size(const size_t&);
	void set(const size_t& position);
	void reset(const size_t& position);
	bool get(const size_t& position);

private:
	void allocate_and_initialize(const unsigned* = nullptr);
	void deallocate();
	bool check_position(const size_t&);

private:
	unsigned* table;
	size_t size;
	size_t max_size;
};

#endif //BITVECTOR_H