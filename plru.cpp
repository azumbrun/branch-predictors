#ifndef PLRU_H
#define PLRU_H
#include "replacement_record.cpp"
#include <cassert>
#include <list>
#include <unordered_map>
#include <iostream>

class PLRU : public ReplacementRecord {
	private:
		int* hc;
		int hc_size;
	public:
		PLRU(int s) : ReplacementRecord(s) {
			hc_size = (size << 1) - 1;
			hc = new int[hc_size];
			for (int i = 0; i < hc_size; i++) {
				hc[i] = 0;
			}
			for (int e = 0; e < size; e++) {
				hc[hc_size-1-e] = size-1-e;
			}
		}

		int evict() {
			int i = 0;
			while (i < size - 1) {
				if (hc[i] == 0) {
					i = 2*i + 2;
				} else {
					i = 2*i + 1;
				}
			}
			return hc[i];
		}
		
		void use(int index) {
			int half = size;
			int i = 0;
			while (half > 1) {
				half = half >> 1;
				if (index < half) {
					hc[i] = 0;
					i = 2*i + 1;
				} else {
					hc[i] = 1;
					index -= half;
					i = 2*i + 2;
				}
			}
		}
};

#endif

