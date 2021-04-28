//Jacob Jakiemiec
//Operating Systems
//Dynamic Memory Allocator
//Block.cpp

#include "Block.hpp"

size_t Block::getSize() {
	return _size;
}

void* Block::getAddress() {
	return _address;
}

void Block::setAddress(void* address) {
	_address = address;
}

void Block::operator=(const Block& right) {
	_address = right._address;
	_size = right._size;
}