class BitVector {
	friend std::ostream& operator<<(std::ostream&, const BitVector&);
	friend std::istream& operator>>(std::istream&, BitVector&);

public:
	BitVector();
	BitVector(const unsigned*, const size_t&);
	BitVector(const BitVector&);
	~BitVector();

	size_t get_size() const;
	void set_size(const size_t);
	void set(const size_t& position, const bool& value);
	bool get(const size_t& position);

private:
	void allocate_and_initialize(const unsigned* = nullptr);
	void deallocate();

private:
	unsigned* table;
	size_t size;
	size_t max_size;
};