#ifndef TLRU_FULLY_ASSOCIATIVE_CACHE_H
#define TLRU_FULLY_ASSOCIATIVE_CACHE_H
#include "fully_associative_cache.cpp"
#include "tlru.cpp"

class TLRUFullyAssociativeCache : public FullyAssociativeCache {
	public:
		TLRUFullyAssociativeCache(int s) : FullyAssociativeCache(s) {
			rr = new TLRU(size);
		}
		TLRUFullyAssociativeCache(int s, bool absolute) : FullyAssociativeCache(s, absolute) {
			rr = new TLRU(size);
		}
		TLRUFullyAssociativeCache(int s, bool absolute, bool wma) : FullyAssociativeCache(s, absolute, wma) {
			rr = new TLRU(size);
		}
};

#endif

