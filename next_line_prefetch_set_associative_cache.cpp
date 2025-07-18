#ifndef NEXT_LINE_PREFETCH_SET_ASSOCIATIVE_CACHE_H
#define NEXT_LINE_PREFETCH_SET_ASSOCIATIVE_CACHE_H

#include <iostream>
#include "set_associative_cache.cpp"
using namespace std;


class NextLinePrefetchSetAssociativeCache : public SetAssociativeCache {
	public:
		NextLinePrefetchSetAssociativeCache(int a) : SetAssociativeCache(a) {
		}
		bool probe(unsigned long long address, bool store) {
			unsigned long long address_p1 = address + 32;
			address_p1 = (address_p1 >> 5);
			int index_p1 = address_p1 & (num_sets-1);

			address = (address >> 5);
			int index = address & (num_sets-1);
			bool result = sets[index]->probe(address, store);

			sets[index_p1]->probe(address_p1, store);
			
			return result;
		}
};

#endif

