//
//#include "Multiset.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
///*
//void test()
//{
//ItemType value;
//Multiset sms;
//assert(sms.insert("cumin"));
//assert(sms.insert("turmeric"));
//assert(sms.insert("cumin"));
//assert(sms.insert("coriander"));
//assert(sms.insert("cumin"));
//assert(sms.insert("turmeric"));
//assert(sms.size() == 6 && sms.uniqueSize() == 3);
//
//assert(sms.getSmallestValue(value) && value == "coriander");
//assert(sms.getSecondSmallestValue(value) && value == "cumin");
//assert(sms.getLeastFrequentValue(value) && value == "coriander");
//
//assert(sms.countIf('>', "cumin") == 2);
//assert(sms.countIf('=', "cumin") == 3);
//assert(sms.countIf('<', "cumin") == 1);
//
//assert(sms.count("turmeric") == 2);
//assert(sms.count("cumin") == 3);
//assert(sms.count("coriander") == 1);
//assert(sms.count("cardamom") == 0);
//
//assert(sms.replace("cumin", "turmeric") && sms.count("turmeric") == 5);
//}
//*/
//
//void test()
//{
//	ItemType value;
//	Multiset ulms;
//	assert(ulms.insert(20));
//	assert(ulms.insert(10));
//	assert(ulms.insert(20));
//	assert(ulms.insert(30));
//	assert(ulms.insert(20));
//	assert(ulms.insert(10));
//	assert(ulms.size() == 6 && ulms.uniqueSize() == 3);
//
//	assert(ulms.getSmallestValue(value) && value == 10);
//	assert(ulms.getSecondSmallestValue(value) && value == 20);
//	assert(ulms.getLeastFrequentValue(value) && value == 30);
//
//	assert(ulms.countIf('>', 20) == 1);
//	assert(ulms.countIf('=', 20) == 3);
//	assert(ulms.countIf('<', 20) == 2);
//
//	assert(ulms.count(10) == 2);
//	assert(ulms.count(20) == 3);
//	assert(ulms.count(30) == 1);
//	assert(ulms.count(40) == 0);
//
//	assert(ulms.replace(20, 10) && ulms.count(10) == 5);
//}
//
//int main()
//{
//
//	test();
//	cout << "Passed all tests" << endl;
//
//	/*
//	Multiset ms;
//	ms.insert("fennel");
//	ms.insert("fennel");
//	ms.insert("fenugreek");
//	ms.insert("fennel");
//	for (int k = 0; k < ms.uniqueSize(); k++)
//	{
//	string x;
//	int n = ms.get(k, x);
//	cout << x << " occurs " << n << " times." << endl;
//	}
//
//	Multiset MS;
//	MS.insert("cinnamon");
//	MS.insert("galangal");
//	MS.insert("cinnamon");
//	string s1;
//	int n1 = MS.get(1, s1);
//	assert((s1 == "cinnamon"  &&  n1 == 2) || (s1 == "galangal"  &&  n1 == 1));
//	string s2;
//	int n2 = MS.get(1, s2);
//	assert(s2 == s1  &&  n2 == n1);
//
//	cout << "Pass all tests" << endl;
//
//
//	ItemType value;
//	Multiset ms1, ms2;
//
//	assert(ms2.getSmallestValue(value) == false);
//	assert(ms2.getSecondSmallestValue(value) == false);
//	assert(ms2.getLeastFrequentValue(value) == false);
//
//	ms1.insert("ABCDE"); ms1.insert("ABCDE");
//	ms1.insert("XYZ"); ms1.insert("GDP");
//
//	ms2.insert("Hello"); ms2.insert("Hello");
//	ms2.insert("PPP");   ms2.insert("PPP");
//	ms2.insert("XYZ");
//
//	assert(ms1.getSmallestValue(value) == true && value == "ABCDE");
//	assert(ms1.getSecondSmallestValue(value) == true && value == "GDP");
//	value = "CS32";
//	assert(ms1.getLeastFrequentValue(value) == false && value == "CS32");
//
//	assert(ms2.getSmallestValue(value) == true && value == "Hello");
//	assert(ms2.getSecondSmallestValue(value) == true && value == "PPP");
//	assert(ms2.getLeastFrequentValue(value) == true && value == "XYZ");
//
//	cout << "Pass all tests" << endl;
//	*/
//	
//	Multiset ms;
//	assert(ms.empty());
//	unsigned long x = 999;
//	assert(ms.get(0, x) == 0 && x == 999);  // x unchanged by get failure
//	assert(!ms.contains(42));
//
//	ms.insert(42);
//	ms.insert(42);
//
//	assert(!ms.getSecondSmallestValue(x) && x == 999);
//	assert(ms.size() == 2 && ms.uniqueSize() == 1);
//	assert(ms.get(1, x) == 0 && x == 999);  // x unchanged by get failure
//	assert(ms.get(0, x) == 2 && x == 42);
//
//	assert(ms.getSmallestValue(x) && x == 42);
//	assert(ms.countIf('=', 42) == 2);
//	assert(ms.countIf('>', 42) == 0);
//	assert(ms.countIf('<', 42) == 0);
//
//	cout << "Passed all tests" << endl;
//
//	Multiset a;   // a can hold at most 1000 distinct items
//	Multiset b;      // b can hold at most 5 distinct items
//	Multiset c;         // c can hold at most DEFAULT_MAX_ITEMS distinct items
//	ItemType v[6] = { 12,23,34,45,56,67 };
//	// No failures inserting 5 distinct items twice each into b
//	for (int k = 0; k < 5; k++)
//	{
//		assert(b.insert(v[k]));
//		assert(b.insert(v[k]));
//	}
//	assert(b.size() == 10 && b.uniqueSize() == 5 && b.count(v[0]) == 2);
//
//	// When two Multisets' contents are swapped, their capacities are swapped
//	// as well:
//	a.swap(b);
//	assert(a.size() == 10 && a.uniqueSize() == 5 && a.count(v[0]) == 2);
//
//	cout << "Pass all tests" << endl;
//
//
//	Multiset d;
//	Multiset e;
//	ItemType f[5] = { 12,34,22,45,11 };
//	ItemType g[7] = { 11, 22, 33, 44, 12, 23 };
//
//	for (int k = 0; k < 5; k++)
//		assert(d.insert(f[k]));
//
//	for (int k = 0; k < 6; k++)
//		assert(e.insert(g[k]));
//
//	e.swap(d);
//	ItemType value1;
//	int count1 = d.get(3, value1);
//	ItemType value2;
//	int count2 = d.get(5, value2);
//	assert(value1 == 44 && count1 == 1 && value2 == 23 && count2 == 1);
//
//	ItemType v1;
//	int c1 = e.get(3, v1);
//	ItemType v2;
//	int c2 = e.get(1, v2);
//	assert(v1 == 45 && c1 == 1 && v2 == 34 && c2 == 1);
//
//	for (int k = 0; k < 5; k++)
//		assert(e.insert(f[k]));
//
//	e.copyIntoOtherMultiset(d);
//	ItemType val1;
//	int ct1 = d.get(1, val1);
//	ItemType val2;
//	int ct2 = d.get(6, val2);
//	ItemType val3;
//	int ct3 = d.get(0, val3);
//	assert(val1 == 22 && ct1 == 3 && val2 == 34 && ct2 == 2 && val3 == 11 && ct3 == 3 && d.size() == 16);
//
//	Multiset A;
//	assert(A.empty());
//	ItemType q = 999;
//	assert(!A.getSmallestValue(q) && q == 999);
//	assert(!A.getSecondSmallestValue(q) && q == 999);
//	ItemType w[18] = { 11, 22, 33, 44, 12, 23,34,45,56,11,22,44,45,56,22,44,45,44 };
//	for (int k = 0; k < 18; k++)
//		assert(A.insert(w[k]));
//	assert(A.size() == 18 && A.uniqueSize()==9);
//	assert(!A.getLeastFrequentValue(q) && q == 999);
//	ItemType i;
//	A.get(3, i);
//	assert(A.erase(i) == 1);
//	assert(A.get(3, i) == 3);
//	assert(A.eraseAll(i) == 3);
//	assert(A.size() == 14 && A.uniqueSize() == 8);
//	ItemType k = 44;
//	assert(!A.contains(k));
//	assert(A.count(k) == 0);
//	k = 56;
//	assert(A.contains(k));
//	assert(A.count(k) == 2);
//	assert(A.getSmallestValue(k) && k == 11);
//	assert(A.getSecondSmallestValue(k) && k == 12);
//	ItemType l = 44;
//	ItemType m = 32;
//	assert(!A.replace(l, m));
//	assert(A.countIf('<', k) == 2);
//	assert(A.countIf('=', k) == 1);
//	k = 22;
//	assert(A.countIf('<', k) == 3);
//
//	Multiset B;
//	assert(B.empty());
//	ItemType j[10] = { 11, 22, 33, 44, 22, 22, 11,33,11,22};
//	for (int k = 0; k < 10; k++)
//	assert(B.insert(j[k]));
//	assert(B.size() == 10 && B.uniqueSize() == 4);
//	assert(B.getLeastFrequentValue(q) && q == 44);
//	assert(B.countIf('>', q) == 0);
//	ItemType p = 11;
//	assert(B.countIf('>', p) == 7);
//
//	Multiset C(B);
//	C = C;
//	assert(C.size() == 10 && C.uniqueSize() == 4);
//	assert(C.getLeastFrequentValue(q) && q == 44);
//	assert(C.countIf('>', q) == 0);
//
//	B = A;
//	k = 12;
//	assert(B.countIf('<', k) == 2);
//	assert(B.countIf('=', k) == 1);
//	k = 22;
//	assert(B.countIf('<', k) == 3);
//
//	
//
//	cerr << "pass" << endl;
//
//}