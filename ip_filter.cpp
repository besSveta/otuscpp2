#include <cassert>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <map>
#include "ip_filter_lib.h"

struct FilterIndexesArrays{
	std::vector<size_t> Indexes1xxx;
	std::vector<size_t> Indexes46_70xx;
	std::vector<size_t> Indexes46;
};

FilterIndexesArrays SortAndGetFilterIndexes(
		IPVector &ip_pool) {

	FilterIndexesArrays Indexes;
	std::sort(ip_pool.begin(), ip_pool.end(), std::greater<std::vector<int>>());
	for (size_t j = 0; j < ip_pool.size(); j++) {
		auto ip_part = ip_pool[j];
		Print_Ip(ip_part);

		if (Filter(ip_part, 0, 1)) {
			Indexes.Indexes1xxx.push_back(j);
		} else {
		if (Filter(ip_part, 0, 46, 70)) {
			Indexes.Indexes46_70xx.push_back(j);
		}
	}
	if (FilterAny(ip_part, 46)) {
		Indexes.Indexes46.push_back(j);
	}

}
return Indexes;
}

void PrintFilters(IPVector &ip_pool) {
auto Indexes = SortAndGetFilterIndexes(ip_pool);
if (Indexes.Indexes1xxx.begin() != Indexes.Indexes1xxx.end()) {
	for (auto t : Indexes.Indexes1xxx) {
		Print_Ip(ip_pool[t]);
	}
}
if (Indexes.Indexes46_70xx.begin() != Indexes.Indexes46_70xx.end()) {
	for (auto t : Indexes.Indexes46_70xx) {
		Print_Ip(ip_pool[t]);
	}
}

if (Indexes.Indexes46.begin() != Indexes.Indexes46.end()) {
	for (auto t :  Indexes.Indexes46) {
		Print_Ip(ip_pool[t]);
	}
}
}

int main(int argc, char const *argv[]) {
try {
	IPVector ip_pool;

	std::vector<int> res;
	//std::ifstream ifs ("ip_filter.tsv");
	for (std::string line; std::getline(std::cin, line);) {
		auto v = split(line, '\t');
		if (MakeInts(split(v.at(0), '.'), res)) {
			ip_pool.push_back(res);
		}
	}
	PrintFilters(ip_pool);

	// TODO reverse lexicographically sort

	// 222.173.235.246
	// 222.130.177.64
	// 222.82.198.61
	// ...
	// 1.70.44.170
	// 1.29.168.152
	// 1.1.234.8
	// TODO filter by first byte and output
	// ip = filter(1)
	// 1.231.69.33
	// 1.87.203.225
	// 1.70.44.170
	// 1.29.168.152
	// 1.1.234.8
	// TODO filter by first and second bytes and output
	// ip = filter(46, 70)
	// 46.70.225.39
	// 46.70.147.26
	// 46.70.113.73
	// 46.70.29.76
	// TODO filter by any byte and output
	// ip = filter_any(46)
	// 186.204.34.46
	// 186.46.222.194
	// 185.46.87.231
	// 185.46.86.132
	// 185.46.86.131
	// 185.46.86.131
	// 185.46.86.22
	// 185.46.85.204
	// 185.46.85.78
	// 68.46.218.208
	// 46.251.197.23
	// 46.223.254.56
	// 46.223.254.56
	// 46.182.19.219
	// 46.161.63.66
	// 46.161.61.51
	// 46.161.60.92
	// 46.161.60.35
	// 46.161.58.202
	// 46.161.56.241
	// 46.161.56.203
	// 46.161.56.174
	// 46.161.56.106
	// 46.161.56.106
	// 46.101.163.119
	// 46.101.127.145
	// 46.70.225.39
	// 46.70.147.26
	// 46.70.113.73
	// 46.70.29.76
	// 46.55.46.98
	// 46.49.43.85
	// 39.46.86.85
	// 5.189.203.46
} catch (const std::exception &e) {
	std::cerr << e.what() << std::endl;
}

return 0;
}

