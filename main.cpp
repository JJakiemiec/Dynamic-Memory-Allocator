//Jacob Jakiemiec
//Operating Systems
//Dynamic Memory Allocator
//main.cpp

#include <string>
using std::string;

#include "BlockManager.hpp"


int main() {
	//Allocate a BlockManager
	BlockManager bm;	

	//Allocate some variables
	void* test0 = bm.allocate(7);
	char* test2 = (char*)bm.allocate('c');

	//Demonstrate that the variables have been allocated
	cout << "Demonstrate that variables can be allocated:" << endl;
	cout << *(int*)test0 << endl;
	cout << *test2 << endl;
	cout << endl;

	//Free a variable and allocate a new variable in its place
	bm.freeValue(test0);
	void* test3 = bm.allocate(8);

	//Demonstrate that the new variable is allocated where the old one way
	cout << "Demonstrate that the free list works" << endl;
	cout << "the following 2 numbers should be the same if the free list works:" << endl;
	cout << *(int*)test3 << endl;
	cout << *(int*)test0 << endl;									//NOTE THIS IS EXTREMELY BAD, IF YOU DEALLOCATE A POINTER, IT HAS UNDEFINED BEHAVIOR, THIS IS JUST TO SHOW THAT THE FREE LIST WORKS
	cout << endl;

	//Allocate an array
	char* charArray = (char*)bm.allocateArray('&', 5);
	charArray[3] = 'y';

	//Demonstrate that allocating an array works
	cout << "Demonstrate that the allocating an array works:" << endl;
	cout << charArray[0] << endl;
	cout << charArray[3] << endl;
	cout << endl;

	//Demonstrate that allocating past the end of the BlockManager Throws and error
	cout << "Demonstrate that allcoating past the end of the Blockmanager throws and error" << endl;
	BlockManager lowSpace;											//create a BlockManager with low space
	int* Bigarray;
	try {
		Bigarray = (int*)lowSpace.allocateArray(1, 1000000000);		//try to allocate a large amount of memory
	}
	catch (const char* error) {
		cout << error << endl;
	}


	return 0;
}