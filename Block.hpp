//Jacob Jakiemiec
//Operating Systems
//Dynamic Memory Allocator
//Block.hpp


//The block is a data structure that holds 2 values:
//	1) A void pointer that points to allocated memory
//	2) a size_t that stores how large the allocated memory is


#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <cstddef>
using std::size_t;

class Block {
public:
	Block() :_size(0), _address((void*)0) {};
	Block(size_t size) : _size(size), _address((void*)0) {};
	Block(size_t size, void* address) : _size(size), _address(address) {};

	size_t getSize();
	void* getAddress();
	void setAddress(void* address);
	void operator=(const Block& right);

private:
	size_t _size;
	void* _address;

};

#endif