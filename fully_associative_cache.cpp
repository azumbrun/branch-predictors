#ifndef FULLY_ASSOCIATIVE_CACHE_H
#define FULLY_ASSOCIATIVE_CACHE_H
#include <iostream>
#include "cache.cpp"
#include "replacement_record.cpp"
using namespace std;

class FullyAssociativeCache : public Cache {
	protected:
		int size;
		cacheEntry* table;
		ReplacementRecord* rr;
		bool absolute = false;
		bool wm = false;
	public:
		FullyAssociativeCache(int s) {
			size = s * 1024 / 32;
			table = new cacheEntry[size];
		}
		FullyAssociativeCache(int s, bool absolute) {
			size = s;
			table = new cacheEntry[size];
			absolute = true;
		}
		FullyAssociativeCache(int s, bool absolute, bool wma) {
			size = s;
			table = new cacheEntry[size];
			absolute = true;
			wm = true;
		}
		bool probe(unsigned long long address, bool store) {
			if (!absolute)
				address = (address >> 5);
			for (int i = 0; i < size; i++) {
				if (table[i].valid) {
					if (table[i].tag == address) {
						rr->use(i);
						return true;
					}
				}
			}
			if (!wm || !store) {
				int replace = rr->evict();
				table[replace].valid = true;
				table[replace].tag = address;
				rr->use(replace);
			}
			return false;
		}
};

#endif

