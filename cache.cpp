#ifndef CACHE_H
#define CACHE_H

class Cache {
	protected:
		struct cacheEntry {
			bool valid = false;
			unsigned long long tag;
		};
	public:
		virtual bool probe(unsigned long long address, bool store) = 0;
};

#endif

