#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <iomanip>
#include "cache.cpp"
#include "direct_map_cache.cpp"
#include "tlru_fully_associative_cache.cpp"
#include "plru_fully_associative_cache.cpp"
#include "set_associative_cache.cpp"
#include "no_allocation_write_miss_set_associative_cache.cpp"
#include "next_line_prefetch_set_associative_cache.cpp"
#include "next_line_prefetch_on_miss_set_associative_cache.cpp"

using namespace std;

int main() {
	// create the predictors and buffers
	string simulations[] = {
		"d 1",
		"d 4",
		"d 16",
		"d 32",
		"fat 16",
		"fap 16",
		"s 2",
		"s 4",
		"s 8",
		"s 16",
		"sam 2",
		"sam 4",
		"sam 8",
		"sam 16",
		"snl 2",
		"snl 4",
		"snl 8",
		"snl 16",
		"snlm 2",
		"snlm 4",
		"snlm 8",
		"snlm 16",
	};

	double best = 0;

	for (string sim : simulations) {
		Cache* cache;
		string sim_name;
		string pred_id;
		int size;

		stringstream sims(sim);
		sims >> pred_id >> size;

		sim_name = "";
		if (pred_id == "d") {
			sim_name += "direct map";
			cache = new DirectMapCache(size);
		} else if (pred_id == "fat") {
			sim_name += "fully assoc true-LRU";
			cache = new TLRUFullyAssociativeCache(size);
		} else if (pred_id == "fap") {
			sim_name += "fully assoc pseudo-LRU";
			cache = new PLRUFullyAssociativeCache(size);
		} else if (pred_id == "s") {
			sim_name += "set assoc ";
			sim_name += to_string(size);
			cache = new SetAssociativeCache(size);
		} else if (pred_id == "sam") {
			sim_name += "set assoc ";
			sim_name += to_string(size);
			sim_name += " skip on write miss";
			cache = new NoAllocationWriteMissSetAssociativeCache(size);
		} else if (pred_id == "snl") {
			sim_name += "set assoc ";
			sim_name += to_string(size);
			sim_name += " prefetch";
			cache = new NextLinePrefetchSetAssociativeCache(size);
		} else if (pred_id == "snlm") {
			sim_name += "set assoc ";
			sim_name += to_string(size);
			sim_name += " prefetch on miss";
			cache = new NextLinePrefetchOnMissSetAssociativeCache(size);
		} else {
			throw std::runtime_error("incorrect cache id");
		}

		if (pred_id == "d") {
			ostringstream oss;
			sim_name += " ";
			oss << setw(2) << size;
			sim_name += oss.str() += "KB";
		}

		unsigned long long num_requests = 0;
		unsigned long long num_hits = 0;
		char SorL;
		unsigned long long address;
		string line;
		while (getline(cin,line)) {
			stringstream s(line);
			s >> SorL >> hex >> address;

			bool store = SorL == 'S' ? true : false;

			bool hit = cache->probe(address, store);

			if (hit)
				num_hits++;

			num_requests++;

		}

		cin.clear();
		cin.seekg(0, ios::beg);

		cout << " " << fixed << setprecision(3)
		<< setw(6) << (100.0 * num_hits / num_requests) << "% - "
		<< sim_name << endl;

		if ((100.0 * num_hits / num_requests) > best)
			best = 100.0 * num_hits / num_requests;
	}

	cout << "Best hit rate:  " << fixed << setprecision(3) << best << '%' << endl;
}

