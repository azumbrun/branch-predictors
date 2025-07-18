#ifndef PLRU_FULLY_ASSOCIATIVE_CACHE_H
#define PLRU_FULLY_ASSOCIATIVE_CACHE_H
#include "fully_associative_cache.cpp"
#include "plru.cpp"

class PLRUFullyAssociativeCache : public FullyAssociativeCache {
	public:
		PLRUFullyAssociativeCache(int s) : FullyAssociativeCache(s) {
			rr = new PLRU(size);
		}
};

#endif

