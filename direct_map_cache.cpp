#ifndef DIRECT_MAP_CACHE_H
#define DIRECT_MAP_CACHE_H
#include <iostream>
#include "cache.cpp"
using namespace std;

class DirectMapCache : public Cache {
	private:
		int size;
		cacheEntry* table;
	public:
		DirectMapCache(int s) {
			size = s * 1024 / 32; // each cache line is 32 bytes long
			table = new cacheEntry[size];
		}
		bool probe(unsigned long long address, bool store) {
			address = (address >> 5);
			int index = address & (size-1);
			if (table[index].valid) {
				if (table[index].tag == address)
					return true;
			}
			table[index].valid = true;
			table[index].tag = address;
			return false;
		}
};

#endif

