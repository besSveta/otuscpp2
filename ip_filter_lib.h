/*
 * ip_filter_lib.h
 *
 *  Created on: 10 мая 2019 г.
 *      Author: sveta
 */
#pragma once
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>

std::vector<std::string> split(const std::string &str, char d);

// Получение из вектора строк, если это возможно, вектора чисел.
// Возвращает истину, если операция выполнена и все числа удалось конвертировать.
bool MakeInts(const std::vector<std::string> &&values, std::vector<int> &result);

// Печать вектора, содержащего части ip адреса.
void Print_Ip(const std::vector<int> &t);

// Печать кортежа, содержащего части ip адреса.
void Print_Ip(const std::tuple<int, int, int, int> &ip_part);


// Фильтры.Параметры представляют собой индекс в векторе и значение.
template<typename T>
bool Filter(const std::vector<T> &values, size_t indx, T filter) {
	if (indx > values.size()) {
		throw "Invalid index";
	}
	return (values[indx] == filter);
}

// заглушка, для функции фильтрации на случай если не задан фильтр.
// Так как в функции с фильтрами проверяется sizeof ...(filters)== 0 то данная функция не вызывается.
template<typename T>
bool Filter(const std::vector<T> &values, size_t indx) {
	return true;
}

// Фильтрация одного адреса: заданы список фильтров на биты, а индекс, чтобы знать какой бит мы проверяем.
template<typename T, typename ...Args>
bool Filter(const std::vector<T> &values, size_t indx, T filter,
		Args ...filters) {
	if (indx > values.size()) {
		throw "Invalid index";
	}
	auto size = sizeof ...(filters);
	if (size > values.size() - 1) {
		throw "Invalid filters count";
	}
	if (size == 0)
		return Filter(values, indx, filter);
	return Filter(values, indx, filter) && Filter(values, indx + 1, filters...);
}
// Фильтрация списка адресов.
/*template<typename T, typename ... Args>
void FilterIps_All(const std::vector<std::tuple<T, T, T, T>> &ip_pool, T filter,
		Args ... filters) {
	for (size_t j = 0; j < ip_pool.size(); j++) {
		auto ip_part = ip_pool[j];
		std::vector<T> t = { std::get<0>(ip_part), std::get<1>(ip_part),
				std::get<2>(ip_part), std::get<3>(ip_part) };

		if (Filter(t, 0, filter, filters ...)) {
			Print_Ip(t);
		}
	}

}*/
bool FilterAny(const std::vector<int> &values, int filter) ;

void SortIps(std::vector<std::tuple<int, int, int, int>> &ip_pool);

void PrintSortedIps(std::vector<std::tuple<int, int, int, int>> &ip_pool);
