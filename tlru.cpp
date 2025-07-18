#ifndef TLRU_H
#define TLRU_H
#include "replacement_record.cpp"
#include <cassert>
#include <list>
#include <unordered_map>
#include <iostream>

class TLRU : public ReplacementRecord {
	private:
		std::list<int> lru_list;
		std::unordered_map<int, std::list<int>::iterator> lru_map;
	public:
		TLRU(int s) : ReplacementRecord(s) {
			for (int i = 0; i < size; i++) {
				// fill up the TLRU record
				use(i);
			}
		}

		int evict() {
			assert(lru_list.size() == size);
			int back = lru_list.back();
			if (lru_list.size() == size) {
				lru_map.erase(back);
				lru_list.pop_back();
			}
			return back;
		}
		
		void use(int index) {
			auto it = lru_map.find(index);
			if (it == lru_map.end()) {
				// Not found
				assert(lru_list.size() < size);
				lru_list.push_front(index);
				lru_map[index] = lru_list.begin();
			} else {
				// Found
				assert(lru_list.size() == size);
				lru_list.splice(lru_list.begin(), lru_list, it->second);
				lru_map[index] = lru_list.begin();
			}
		}
};

#endif

