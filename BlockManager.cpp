//Jacob Jakiemiec
//Operating Systems
//Dynamic Memory Allocator
//BlockManager.cpp

#include "BlockManager.hpp"

BlockManager::BlockManager() : _size(PAGESIZE * 20) {
	_buff = mmap((void*)0, _size, PROT_READ + PROT_WRITE, MAP_ANONYMOUS + MAP_SHARED, -1, 0);
	if (_buff == MAP_FAILED) { perror("mmap"); exit(1); }
}

BlockManager::BlockManager(size_t size) {
	_size = determineAllocationSize(size);
	_buff = mmap((void*)0, _size, PROT_READ + PROT_WRITE, MAP_ANONYMOUS + MAP_SHARED, -1, 0);
	if (_buff == MAP_FAILED) { perror("mmap"); exit(1); }
}

void BlockManager::freeValue(void* address) {
	Block value;
	try {
		value = _allocatedList.at(address);
	}
	catch (...) {
		return;
	}
	_allocatedList.erase(address);
	_freeList.insert(pair<void*, Block>(address, value));
}

BlockManager::~BlockManager(){
	munmap(_buff, _size);
}

size_t BlockManager::determineAllocationSize(size_t size) {
	return (size >> 12) * PAGESIZE + PAGESIZE;
}

size_t BlockManager::region_for_size(uint64_t size) {	//TAKEN FROM POWER OF 2 ALLOCATION LECTURE
	if (size <= 8) return 0;
	else return (__builtin_clzll((size + 3) / 4 - 1) ^ 63);
}