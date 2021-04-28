//Jacob Jakiemiec
//Operating Systems
//Dynamic Memory Allocator
//BlockManager.hpp



//The BlockManager is the Dynamic memory allocator itself
//Since it uses NMAP, it will only work on Linux systems
//To use the BlockManager:
//	1) create a Blockmanager object, this can be done internally by the OS or at the beginning of a program
//	   EXAMPLE:
//	   BlockManager bm;
//
//	2) allocate space by using the allocate() or allocateArray() function
//	   allocate() has one parameter: the variable that you want to store
//	   allocateArray takes two parameters: the variable that you want to store and the size of the array
//	   NOTE: allocate() and allocateArray() returns a void pointer, if you want to store it, you have to cast it to the type you need
//	   EXAMPLE:
//	   int* chr = (int*)bm.allocate(1);
//	   char* intArray = (char*)bm.alloateArray('c', 10);
//
//	3) Deallocate memory either manually with freeValue() or let garbage collection deallocate
//	   freeValue() has one parameter: the void pointer of the memory you want to deallocate
//	   NOTE: freeValue takes a void pointer, you will need to cast you pointer to a void pointer if you want to deallocate it
//	   EXAMPLE:
//	   bm.freeValue((void*)chr);
//

//BlockManager is not thread safe
//BlockManager is not exception safe
//	   BlockManager throws if you try to allocate past the size of the Blockmanager

#ifndef BLOCKMANAGER_HPP
#define BLOCKMANAGER_HPP

#include "Block.hpp"

#include <map>
using std::map;
using std::pair;
#include <iostream>
using std::cout;
using std::endl;
#include <sys/mman.h>


class BlockManager {
public:

	BlockManager();
	BlockManager(size_t size);
	void freeValue(void* address);
	~BlockManager();
	



	template <typename type>
	void* allocate(type value) {
		return allocateWorker(value, sizeof(type));
	}

	template <typename type>
	void* allocateArray(type value, size_t size) {
		return allocateWorker(value, sizeof(type) * size);
	}




private:
	const size_t PAGESIZE = 4096;		//size of one page of the page table

	size_t _size;
	size_t _allocatedSize = 0;
	void* _buff;
	map<void*, Block> _allocatedList;
	map<void*, Block> _freeList;

	size_t determineAllocationSize(size_t size);
	size_t region_for_size(uint64_t size);

	template <typename type>
	void* allocateWorker(type value, size_t memorysize) {
		if (_allocatedSize + memorysize > _size) {
			throw "ERROR: out of space";
		}
		Block newBlock(memorysize, _buff);
		for (auto it = _freeList.begin(); it != _freeList.end(); it++) {
			if (memorysize == it->second.getSize()) {
				newBlock.setAddress(it->second.getAddress());
				_allocatedList.insert(pair<void*, Block>(_buff, newBlock));
				*(type*)it->second.getAddress() = value;
				_freeList.erase(it);
				return newBlock.getAddress();
			}
		}
		_allocatedList.insert(pair<void*, Block>(_buff, newBlock));
		*(type*)_buff = value;
		_buff += memorysize;
		_allocatedSize += memorysize;
		return newBlock.getAddress();
	}

	
};

#endif