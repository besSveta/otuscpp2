/*
 * ip_filter_lib.cpp
 *
 *  Created on: 10 мая 2019 г.
 *      Author: sveta
 */

#include "ip_filter_lib.h"
// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
// Разбиение массива по разделителю.
std::vector<std::string> split(const std::string &str, char d) {
	std::vector<std::string> r;

	auto start = 0;
	auto stop = str.find_first_of(d);
	while (stop != std::string::npos) {
		r.push_back(str.substr(start, stop - start));
		start = stop + 1;
		stop = str.find_first_of(d, start);
	}

	r.push_back(str.substr(start));

	return r;
}

// Разбиение массива по разделителю. С использованием итераторов.
std::vector<std::string> split2(const std::string &str, char d) {
	std::vector<std::string> r;

	auto stop = std::find(begin(str), end(str), d);
	auto start = begin(str);
	while (stop != end(str)) {
		auto s = std::string(start, stop);
		r.push_back(s);
		start = stop + 1;
		stop = std::find(start, end(str), d);
	}
	r.push_back(std::string(start, stop));

	return r;
}

// Получение из вектора строк, если это возможно, вектора чисел.
// Возвращает истину, если операция выполнена и все числа удалось конвертировать.
bool MakeInts(const std::vector<std::string> &&values, std::vector<int> &result) {
	try {
		result.clear();
		result.reserve(values.size());
		int val;
		auto i = 0;
		for (auto t : values) {
			val = std::stoi(t);
			result.push_back(val);
			i++;
		}
		return (i == values.size());
	} catch (const std::exception &e) {
		return false;
	}

}
// Печать вектора, содержащего части ip адреса.
void Print_Ip(const std::vector<int> &t) {
	if (t.size() == 0)
		std::cout << "Incorrect ip";
	std::cout << t[0];
	std::cout << ".";
	std::cout << t[1];
	std::cout << ".";
	std::cout << t[2];
	std::cout << ".";
	std::cout << t[3];
	std::cout << std::endl;
}

bool FilterAny(const std::vector<int> &values, int filter) {
	for (auto val : values) {
		if (val == filter) {
			return true;
		}
	}
	return false;
}

// Хотя бы одна часть адреса равна данному числу.
void FilterIps_Any(const IPVector&ip_pool,
		int filter) {
	for (size_t j = 0; j < ip_pool.size(); j++) {
		auto ip_part = ip_pool[j];
		if (FilterAny(ip_part, filter))
			Print_Ip(ip_part);
	}

}
void SortIps(IPVector&ip_pool){
	std::sort(ip_pool.begin(), ip_pool.end(),std::greater<std::vector<int>>());
}

// Сотрировка и вывод адресов.
void PrintSortedIps(IPVector&ip_pool) {

	SortIps(ip_pool);
	for (size_t j = 0; j < ip_pool.size(); j++) {
		Print_Ip( ip_pool[j]);

	}
}

