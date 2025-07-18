#ifndef NO_ALLOCATION_WRITE_MISS_SET_ASSOCIATIVE_CACHE_H
#define NO_ALLOCATION_WRITE_MISS_SET_ASSOCIATIVE_CACHE_H

#include <iostream>
#include "cache.cpp"
using namespace std;


class NoAllocationWriteMissSetAssociativeCache : public Cache{
	private:
		int associativity;
		int num_lines;
		int num_sets;
		TLRUFullyAssociativeCache** sets;
	public:
		NoAllocationWriteMissSetAssociativeCache(int a) {
			num_lines = SET_ASSOCIATIVE_CACHE_SIZE * 1024 / 32;
			associativity = a;
			num_sets = num_lines / associativity;
			sets = new TLRUFullyAssociativeCache*[num_sets];
			
			for (int i = 0; i < num_sets; i++) {
				sets[i] = new TLRUFullyAssociativeCache(associativity, true, true);
			}
		}
		bool probe(unsigned long long address, bool store) {
			address = (address >> 5);
			int index = address & (num_sets-1);
			return sets[index]->probe(address, store);
		}
};

#endif

