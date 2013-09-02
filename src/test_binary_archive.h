#pragma once

#include "binary_archive.h"
#include <string>
#include <vector>
#include <assert.h>

struct st_test2
{
	std::string _string;
	int _int;

	template<class Archive>
	void serialize(Archive & ar)
	{
		ar & _string;
		ar & _int;
	}

	bool operator==(const st_test2 & st) const
	{
		return ((_string == st._string) && 
			(_int == st._int));
	}
};

struct st_test
{
	int _int;
	float _float;
	unsigned long _ulong;
	std::string _string;
	st_test2 _st_test;
	
	template<class Archive>
	void serialize(Archive & ar)
	{
		ar & _int;
		ar & _float;
		ar & _ulong;
		ar & _string;
		ar & _st_test;
	}

	bool operator==(const st_test& st) const
	{
		return ((_int == st._int) && 
			(_float == st._float) &&
			(_ulong == st._ulong) &&
			(_string == st._string) &&
			(_st_test == st._st_test));
	}
};

class test_binary_archive
{
public:
	void run_test()
	{
		test_char();
		test_uchar();
		test_int();
		test_uint();
		test_long();
		test_ulong();
		test_float();
		test_double();
		test_string();
		test_vector();
		test_struct();
		test_vector_struct();
	}
private:
	void test_char();
	void test_uchar();
	void test_int();
	void test_uint();
	void test_long();
	void test_ulong();
	void test_float();
	void test_double();
	void test_string();
	void test_vector();
	void test_struct();
	void test_vector_struct();

};

void test_binary_archive::test_int()
{
	int a1, a2;
	binary_oarchive oa;
	oa << a1;
	binary_iarchive ia(oa.get_buffer(), oa.get_size());
	ia >> a2;
	assert(a1 == a2);
}

void test_binary_archive::test_uint()
{
	unsigned int a1, a2;
	binary_oarchive oa;
	oa << a1;
	binary_iarchive ia(oa.get_buffer(), oa.get_size());
	ia >> a2;
	assert(a1 == a2);
}

void test_binary_archive::test_char()
{
	char a1, a2;
	binary_oarchive oa;
	oa << a1;
	binary_iarchive ia(oa.get_buffer(), oa.get_size());
	ia >> a2;
	assert(a1 == a2);
}

void test_binary_archive::test_uchar()
{
	unsigned char a1, a2;
	binary_oarchive oa;
	oa << a1;
	binary_iarchive ia(oa.get_buffer(), oa.get_size());
	ia >> a2;
	assert(a1 == a2);
}

void test_binary_archive::test_long()
{
	long a1, a2;
	binary_oarchive oa;
	oa << a1;
	binary_iarchive ia(oa.get_buffer(), oa.get_size());
	ia >> a2;
	assert(a1 == a2);
}

void test_binary_archive::test_ulong()
{
	unsigned long a1, a2;
	binary_oarchive oa;
	oa << a1;
	binary_iarchive ia(oa.get_buffer(), oa.get_size());
	ia >> a2;
	assert(a1 == a2);
}

void test_binary_archive::test_float()
{
	float a1, a2;
	binary_oarchive oa;
	oa << a1;
	binary_iarchive ia(oa.get_buffer(), oa.get_size());
	ia >> a2;
	assert(a1 == a2);
}

void test_binary_archive::test_double()
{
	double a1, a2;
	binary_oarchive oa;
	oa << a1;
	binary_iarchive ia(oa.get_buffer(), oa.get_size());
	ia >> a2;
	assert(a1 == a2);
}

void test_binary_archive::test_string()
{
	std::string a1, a2;
	binary_oarchive oa;
	oa << a1;
	binary_iarchive ia(oa.get_buffer(), oa.get_size());
	ia >> a2;
	assert(a1 == a2);
}

void test_binary_archive::test_vector()
{
	std::vector<int> a1, a2;
	a1.push_back(4);
	a1.push_back(5);
	a1.push_back(6);
	binary_oarchive oa;
	oa << a1;
	binary_iarchive ia(oa.get_buffer(), oa.get_size());
	ia >> a2;
	assert(a1 == a2);
}

void test_binary_archive::test_struct()
{
	st_test st, st2;
	st._int = 1;
	st._ulong = 3;
	st._float = 8.9f;
	st._string = "this is a test for struct serialize";
	binary_oarchive oa;
	oa << st;
	binary_iarchive ia(oa.get_buffer(), oa.get_size());
	ia >> st2;
	assert(st == st2);
}

void test_binary_archive::test_vector_struct()
{
	std::vector<st_test> vst, vst2;
	st_test st;
	st._int = 1;
	st._ulong = 3;
	st._float = 8.9f;
	st._string = "this is a test for struct serialize";
	st_test2 st2;
	st2._int = 89999;
	st2._string = "this test for st_test2";
	st._st_test = st2;
	vst.push_back(st);
	st._string = "this the second test";
	st._int = 100;
	st2._string = "welcome to use binary_archive";
	st._st_test = st2;
	vst.push_back(st);
	binary_oarchive oa;
	oa << vst;
	binary_iarchive ia(oa.get_buffer(), oa.get_size());
	ia >> vst2;
	assert(vst == vst2);
}