/*
 * test_ip_filter.cpp
 *
 *  Created on: 10 мая 2019 г.
 *      Author: sveta
 */
#define BOOST_TEST_MODULE ip_filter_test_module
#include <boost/test/included/unit_test.hpp>
#include "ip_filter_lib.h"

BOOST_AUTO_TEST_SUITE(ip_filter_test_suite)

BOOST_AUTO_TEST_CASE(ip_filter__split_test_case)
{
	auto ip_vector=split("11.1.21.1", '.');
	BOOST_CHECK(ip_vector.size()==4);
	BOOST_REQUIRE_EQUAL(ip_vector[2],"21");
}

BOOST_AUTO_TEST_CASE(ip_filter_MakeInts_test_case)
{
	auto ip_vector=split("11.1.21.1", '.');
	std::vector<int> res;
	BOOST_REQUIRE_EQUAL(MakeInts(std::move(ip_vector), res),true);
}

BOOST_AUTO_TEST_CASE(ip_filter_4Filters_test_case)
{
	std::vector<int> res;
	MakeInts(split("11.1.21.1", '.'), res);;

	BOOST_REQUIRE_EQUAL(Filter(res, 0, 11,1,21,1),true);
	BOOST_REQUIRE_EQUAL(Filter(res, 0, 11,7),false);
}

BOOST_AUTO_TEST_CASE(ip_filter_AnyFilte_test_case)
{
	std::vector<int> res;
	MakeInts(split("11.1.21.1", '.'), res);

	BOOST_REQUIRE_EQUAL(FilterAny(res,21),true);
	BOOST_REQUIRE_EQUAL(FilterAny(res,22), false);
}

BOOST_AUTO_TEST_CASE(ip_filter_Sort_test_case)
{
	std::vector<int> res;

	std::vector<std::vector<int>> ip_pool;
	MakeInts(split("1.1.1.1", '.'), res);
	ip_pool.push_back(res);
	MakeInts(split("1.2.1.1", '.'), res);
	ip_pool.push_back(res);
	MakeInts(split("1.10.1.1", '.'), res);
	ip_pool.push_back(res);

	SortIps(ip_pool);
	//PrintSortedIps(ip_pool);
	BOOST_REQUIRE_EQUAL(ip_pool[0][1],10);
	BOOST_REQUIRE_EQUAL(ip_pool[1][1],2);
	BOOST_REQUIRE_EQUAL(ip_pool[2][1],1);
}

BOOST_AUTO_TEST_SUITE_END()



