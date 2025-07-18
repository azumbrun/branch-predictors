#ifndef REPLACEMENT_RECORD_H
#define REPLACEMENT_RECORD_H
#include <cassert>
#include <list>

class ReplacementRecord {
	protected:
		int size;
	public:
		ReplacementRecord(int s) {
			size = s;
		}
		virtual int evict() = 0;
		virtual void use(int index) = 0;
};

#endif

