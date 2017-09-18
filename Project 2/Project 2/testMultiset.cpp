// tester.cpp
// To test HW 1 Problem 5, uncomment the following line:
// #define TESTNEW

#ifdef TESTNEW
#include "newMultiset.h"
#else
#include "Multiset.h"
#endif

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <type_traits>
#include <cassert>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
using namespace std;

//static ItemType DUMMY = 123;
//static ItemType DEFAULT = 0;
//static ItemType ARRAY[6] = { 10, 20, 30, 40, 50, 60 };
//
//const int SPEC_MAX = 200;
//
//void testone(int n)
//{
//	Multiset m;
//	switch (n)
//	{
//	default: {
//		cout << "Bad argument" << endl;
//	} break; case  1: {
//		assert((is_same<decltype(&Multiset::empty),
//			bool (Multiset::*)() const>::value));
//	} break; case  2: {
//		assert((is_same<decltype(&Multiset::size),
//			int (Multiset::*)() const>::value));
//	} break; case  3: {
//		assert((is_same<decltype(&Multiset::uniqueSize),
//			int (Multiset::*)() const>::value));
//	} break; case  4: {
//		assert((is_same<decltype(&Multiset::contains),
//			bool (Multiset::*)(const ItemType&) const>::value));
//	} break; case  5: {
//		assert((is_same<decltype(&Multiset::count),
//			int (Multiset::*)(const ItemType&) const>::value));
//	} break; case  6: {
//		assert((is_same<decltype(&Multiset::get),
//			int (Multiset::*)(int, ItemType&) const>::value));
//	} break; case  7: {
//		assert((is_same<decltype(&Multiset::getLeastFrequentValue),
//			bool (Multiset::*)(ItemType&) const>::value));
//	} break; case  8: {
//		assert((is_same<decltype(&Multiset::getSmallestValue),
//			bool (Multiset::*)(ItemType&) const>::value));
//	} break; case  9: {
//		assert((is_same<decltype(&Multiset::getSecondSmallestValue),
//			bool (Multiset::*)(ItemType&) const>::value));
//	} break; case 10: {
//		assert((is_same<decltype(&Multiset::countIf),
//			int (Multiset::*)(char, ItemType) const>::value));
//	} break; case 11: {
//		assert((is_same<decltype(&Multiset::copyIntoOtherMultiset),
//			void (Multiset::*)(Multiset&) const>::value));
//	} break; case 12: {
//		assert(m.empty());
//	} break; case 13: {
//		assert(m.size() == 0);
//	} break; case 14: {
//		assert(m.uniqueSize() == 0);
//	} break; case 15: {
//		assert(m.erase(DEFAULT) == 0 && m.size() == 0);
//	} break; case 16: {
//		assert(m.eraseAll(DEFAULT) == 0 && m.size() == 0);
//	} break; case 17: {
//		assert(!m.contains(DEFAULT));
//	} break; case 18: {
//		assert(m.count(DEFAULT) == 0);
//	} break; case 19: {
//		ItemType x = DUMMY;
//		assert(m.get(0, x) == 0);
//	} break; case 20: {
//		ItemType x = DUMMY;
//		m.get(0, x);
//		assert(x == DUMMY);
//	} break; case 21: {
//		ItemType x = DUMMY;
//		assert(!m.getLeastFrequentValue(x));
//	} break; case 22: {
//		ItemType x = DUMMY;
//		m.getLeastFrequentValue(x);
//		assert(x == DUMMY);
//	} break; case 23: {
//		ItemType x = DUMMY;
//		assert(!m.getSmallestValue(x));
//	} break; case 24: {
//		ItemType x = DUMMY;
//		m.getSmallestValue(x);
//		assert(x == DUMMY);
//	} break; case 25: {
//		ItemType x = DUMMY;
//		assert(!m.getSecondSmallestValue(x));
//	} break; case 26: {
//		ItemType x = DUMMY;
//		m.getSecondSmallestValue(x);
//		assert(x == DUMMY);
//	} break; case 27: {
//		assert(!m.replace(DEFAULT, ARRAY[0]));
//	} break; case 28: {
//		m.replace(DEFAULT, ARRAY[0]);
//		ItemType x = DUMMY;
//		m.get(0, x);
//		assert(x == DUMMY);
//	} break; case 29: {
//		assert(m.countIf('@', DEFAULT) == -1);
//	} break; case 30: {
//		assert(m.countIf('=', DEFAULT) == 0);
//	} break; case 31: {
//		assert(m.insert(DUMMY));
//	} break; case 32: {
//		m.insert(DUMMY);
//		assert(!m.empty());
//	} break; case 33: {
//		m.insert(DUMMY);
//		assert(m.size() == 1);
//	} break; case 34: {
//		m.insert(DUMMY);
//		assert(m.uniqueSize() == 1);
//	} break; case 35: {
//		m.insert(DUMMY);
//		assert(m.contains(DUMMY));
//	} break; case 36: {
//		m.insert(DUMMY);
//		assert(m.count(DUMMY) == 1);
//	} break; case 37: {
//		m.insert(ARRAY[0]);
//		ItemType x = DUMMY;
//		assert(m.get(0, x) == 1);
//	} break; case 38: {
//		m.insert(ARRAY[0]);
//		ItemType x = DUMMY;
//		m.get(0, x);
//		assert(x == ARRAY[0]);
//	} break; case 39: {
//		m.insert(ARRAY[0]);
//		ItemType x = DUMMY;
//		assert(m.getLeastFrequentValue(x));
//	} break; case 40: {
//		m.insert(ARRAY[0]);
//		ItemType x = DUMMY;
//		m.getLeastFrequentValue(x);
//		assert(x == ARRAY[0]);
//	} break; case 41: {
//		m.insert(ARRAY[0]);
//		ItemType x = DUMMY;
//		assert(m.getSmallestValue(x));
//	} break; case 42: {
//		m.insert(ARRAY[0]);
//		ItemType x = DUMMY;
//		m.getSmallestValue(x);
//		assert(x == ARRAY[0]);
//	} break; case 43: {
//		m.insert(ARRAY[0]);
//		ItemType x = DUMMY;
//		assert(!m.getSecondSmallestValue(x));
//	} break; case 44: {
//		m.insert(ARRAY[0]);
//		ItemType x = DUMMY;
//		m.getSecondSmallestValue(x);
//		assert(x == DUMMY);
//	} break; case 45: {
//		m.insert(ARRAY[0]);
//		assert(!m.replace(ARRAY[1], ARRAY[2]));
//		assert(m.size() == 1 && m.count(ARRAY[0]) == 1 && m.count(ARRAY[2]) == 0);
//	} break; case 46: {
//		m.insert(ARRAY[0]);
//		assert(m.replace(ARRAY[0], ARRAY[1]));
//		assert(m.size() == 1 && m.count(ARRAY[1]) == 1 && m.count(ARRAY[0]) == 0);
//	} break; case 47: {
//		m.insert(ARRAY[0]);
//		assert(m.replace(ARRAY[0], ARRAY[0]));
//		assert(m.size() == 1 && m.uniqueSize() == 1 && m.count(ARRAY[0]) == 1);
//	} break; case 48: {
//		m.insert(ARRAY[0]);
//		assert(m.countIf('#', ARRAY[0]) == -1);
//	} break; case 49: {
//		m.insert(ARRAY[0]);
//		assert(m.countIf('=', ARRAY[0]) == 1);
//	} break; case 50: {
//		m.insert(ARRAY[0]);
//		assert(m.countIf('<', ARRAY[0]) == 0);
//	} break; case 51: {
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[0]);
//		ItemType x = DUMMY;
//		assert(m.getSecondSmallestValue(x));
//	} break; case 52: {
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[0]);
//		ItemType x = DUMMY;
//		m.getSmallestValue(x);
//		assert(x == ARRAY[0]);
//		m.getSecondSmallestValue(x);
//		assert(x == ARRAY[1]);
//	} break; case 53: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		ItemType x = DUMMY;
//		m.getSmallestValue(x);
//		assert(x == ARRAY[0]);
//		m.getSecondSmallestValue(x);
//		assert(x == ARRAY[1]);
//	} break; case 54: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[0]);
//		ItemType x = DUMMY;
//		assert(m.getSmallestValue(x) && x == ARRAY[0]);
//		x = DUMMY;
//		assert(!m.getSecondSmallestValue(x) && x == DUMMY);
//	} break; case 55: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		assert(!m.empty() && m.size() == 2 && m.uniqueSize() == 2);
//	} break; case 56: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		assert(m.contains(ARRAY[0]) && m.contains(ARRAY[1]));
//	} break; case 57: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		assert(m.count(ARRAY[0]) == 1 && m.count(ARRAY[1]) == 1);
//	} break; case 58: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[0]);
//		assert(m.size() == 3 && m.uniqueSize() == 2);
//	} break; case 59: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[0]);
//		assert(m.contains(ARRAY[0]) && m.contains(ARRAY[1]));
//	} break; case 60: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[0]);
//		assert(m.count(ARRAY[0]) == 2 && m.count(ARRAY[1]) == 1);
//	} break; case 61: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[0]);
//		ItemType x = DUMMY;
//		m.get(0, x);
//		assert(x == ARRAY[0] || x == ARRAY[1]);
//	} break; case 62: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[0]);
//		ItemType x = DUMMY;
//		m.get(0, x);
//		ItemType y = DUMMY;
//		m.get(0, y);
//		assert(x == y  &&  x != DUMMY);
//	} break; case 63: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[0]);
//		int n0 = 0;
//		int n1 = 0;
//		int nx = 0;
//		ItemType x;
//		for (int k = 0; k < 2; k++)
//		{
//			m.get(k, x);
//			if (x == ARRAY[0])
//				n0++;
//			else if (x == ARRAY[1])
//				n1++;
//			else
//				nx++;
//		}
//		assert(m.get(2, x) == 0);
//		assert(n0 == 1 && n1 == 1 && nx == 0);
//	} break; case 64: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[0]);
//		int n[2] = { 0 };
//		for (int k = 0; k < 2; k++)
//		{
//			ItemType x;
//			int ct = m.get(k, x);
//			bool found = false;
//			for (int i = 0; i < 2; i++)
//			{
//				if (x == ARRAY[i])
//				{
//					n[i] += ct;
//					found = true;
//					break;
//				}
//			}
//			assert(found);
//		}
//		assert(n[0] == 2 && n[1] == 1);
//	} break; case 65: {
//		m.insert(ARRAY[3]);
//		m.insert(ARRAY[3]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[4]);
//		m.insert(ARRAY[4]);
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[4]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[2]);
//		m.insert(ARRAY[4]);
//		assert(m.size() == 10 && m.uniqueSize() == 5);
//		int counts[5] = { 1, 2, 1, 2, 4 };
//		ItemType a[5] = { DUMMY, DUMMY, DUMMY, DUMMY, DUMMY };
//		int n[5];
//		for (int k = 0; k < 5; k++)
//			n[k] = m.get(k, a[k]);
//		for (int j = 0; j < 5; j++)
//		{
//			int k;
//			for (k = 0; k < 5; k++)
//			{
//				if (a[k] == ARRAY[j])
//				{
//					assert(n[k] == counts[j]);
//					break;
//				}
//			}
//			assert(k < 5);
//		}
//	} break; case 66: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[0]);
//		assert(m.eraseAll(ARRAY[0]) == 2);
//	} break; case 67: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[0]);
//		m.eraseAll(ARRAY[0]);
//		assert(!m.empty() && m.size() == 1 && m.uniqueSize() == 1);
//	} break; case 68: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[0]);
//		m.eraseAll(ARRAY[0]);
//		assert(m.count(ARRAY[0]) == 0 && m.count(ARRAY[1]) == 1);
//	} break; case 69: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[0]);
//		m.eraseAll(ARRAY[1]);
//		assert(!m.empty() && m.size() == 2 && m.uniqueSize() == 1);
//		assert(m.count(ARRAY[0]) == 2 && m.count(ARRAY[1]) == 0);
//	} break; case 70: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[0]);
//		m.eraseAll(ARRAY[0]);
//		m.erase(ARRAY[1]);
//		assert(m.count(ARRAY[0]) == 0 && m.count(ARRAY[1]) == 0);
//	} break; case 71: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[0]);
//		m.eraseAll(ARRAY[0]);
//		m.erase(ARRAY[1]);
//		assert(m.size() == 0 && m.uniqueSize() == 0);
//	} break; case 72: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[2]);
//		assert(m.erase(ARRAY[1]) == 1);
//	} break; case 73: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[2]);
//		m.erase(ARRAY[1]);
//		assert(m.count(ARRAY[1]) == 1 && m.uniqueSize() == 3);
//	} break; case 74: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[2]);
//		m.erase(ARRAY[1]);
//		m.erase(ARRAY[2]);
//		m.erase(ARRAY[1]);
//		m.insert(ARRAY[3]);
//		assert(m.uniqueSize() == 2 && m.count(ARRAY[1]) == 0 &&
//			m.count(ARRAY[2]) == 0);
//	} break; case 75: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		assert(m.erase(ARRAY[2]) == 0 && m.uniqueSize() == 2);
//	} break; case 76: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[0]);
//		m.erase(ARRAY[0]);
//		m.erase(ARRAY[0]);
//		ItemType x;
//		assert(m.get(0, x) == 1 && x == ARRAY[1]);
//	} break; case 77: {
//		m.insert(DEFAULT);
//		assert(m.size() == 1 && m.uniqueSize() == 1 &&
//			m.contains(DEFAULT) && m.count(DEFAULT) == 1);
//	} break; case 78: {
//		m.insert(DEFAULT);
//		m.erase(DEFAULT);
//		assert(m.size() == 0 && m.uniqueSize() == 0 &&
//			!m.contains(DEFAULT) && m.count(DEFAULT) == 0);
//	} break; case 79: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[2]);
//		ItemType x;
//		assert(m.get(-1, x) == 0);
//	} break; case 80: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[2]);
//		ItemType x = DUMMY;
//		m.get(-1, x);
//		assert(x == DUMMY);
//	} break; case 81: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[2]);
//		ItemType x;
//		assert(m.get(3, x) == 0);
//	} break; case 82: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[2]);
//		ItemType x = DUMMY;
//		m.get(3, x);
//		assert(x == DUMMY);
//	} break; case 83: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[2]);
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[3]);
//		m.insert(ARRAY[3]);
//		m.insert(ARRAY[1]);
//		ItemType x = DUMMY;
//		assert(m.getLeastFrequentValue(x));
//	} break; case 84: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[2]);
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[3]);
//		m.insert(ARRAY[3]);
//		m.insert(ARRAY[1]);
//		ItemType x = DUMMY;
//		m.getLeastFrequentValue(x);
//		assert(x == ARRAY[2]);
//	} break; case 85: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[2]);
//		m.insert(ARRAY[3]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[3]);
//		m.insert(ARRAY[3]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[1]);
//		ItemType x = DUMMY;
//		assert(!m.getLeastFrequentValue(x));
//	} break; case 86: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[2]);
//		m.insert(ARRAY[3]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[3]);
//		m.insert(ARRAY[3]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[1]);
//		ItemType x = DUMMY;
//		m.getLeastFrequentValue(x);
//		assert(x == DUMMY);
//	} break; case 87: {
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[3]);
//		m.insert(ARRAY[2]);
//		m.insert(ARRAY[2]);
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[2]);
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[3]);
//		ItemType x = DUMMY;
//		m.getSmallestValue(x);
//		assert(x == ARRAY[0]);
//	} break; case 88: {
//		m.insert(ARRAY[2]);
//		m.insert(ARRAY[4]);
//		m.insert(ARRAY[2]);
//		m.insert(ARRAY[3]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[3]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[2]);
//		m.insert(ARRAY[4]);
//		m.insert(ARRAY[0]);
//		ItemType x = DUMMY;
//		m.getSmallestValue(x);
//		assert(x == ARRAY[0]);
//	} break; case 89: {
//		m.insert(ARRAY[2]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[3]);
//		m.insert(ARRAY[0]);
//		m.erase(ARRAY[1]);
//		m.erase(ARRAY[0]);
//		ItemType x = DUMMY;
//		m.getSmallestValue(x);
//		assert(x == ARRAY[2]);
//	} break; case 90: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[4]);
//		m.insert(ARRAY[2]);
//		m.insert(ARRAY[4]);
//		m.insert(ARRAY[3]);
//		ItemType x = DUMMY;
//		m.getSecondSmallestValue(x);
//		assert(x == ARRAY[1]);
//	} break; case 91: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[2]);
//		m.insert(ARRAY[4]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[4]);
//		m.insert(ARRAY[3]);
//		ItemType x = DUMMY;
//		m.getSecondSmallestValue(x);
//		assert(x == ARRAY[1]);
//	} break; case 92: {
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[2]);
//		m.insert(ARRAY[4]);
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[4]);
//		m.insert(ARRAY[3]);
//		ItemType x = DUMMY;
//		m.getSecondSmallestValue(x);
//		assert(x == ARRAY[1]);
//	} break; case 93: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[3]);
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[3]);
//		m.insert(ARRAY[2]);
//		ItemType x = DUMMY;
//		m.getSecondSmallestValue(x);
//		assert(x == ARRAY[1]);
//	} break; case 94: {
//		m.insert(ARRAY[2]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[3]);
//		m.insert(ARRAY[0]);
//		m.erase(ARRAY[1]);
//		m.erase(ARRAY[0]);
//		ItemType x = DUMMY;
//		m.getSecondSmallestValue(x);
//		assert(x == ARRAY[3]);
//	} break; case 95: {
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[3]);
//		assert(!m.replace(ARRAY[2], ARRAY[4]) && m.uniqueSize() == 3 &&
//			m.size() == 3 && m.count(ARRAY[0]) == 1 &&
//			m.count(ARRAY[1]) == 1 && m.count(ARRAY[3]) == 1);
//	} break; case 96: {
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[3]);
//		assert(m.replace(ARRAY[0], ARRAY[2]));
//	} break; case 97: {
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[3]);
//		m.replace(ARRAY[0], ARRAY[2]);
//		assert(m.uniqueSize() == 3 && m.size() == 3 &&
//			m.count(ARRAY[1]) == 1 && m.count(ARRAY[2]) == 1 &&
//			m.count(ARRAY[3]) == 1 && m.count(ARRAY[0]) == 0);
//	} break; case 98: {
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[3]);
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[3]);
//		m.insert(ARRAY[3]);
//		m.replace(ARRAY[0], ARRAY[2]);
//		assert(m.uniqueSize() == 3 && m.size() == 6 &&
//			m.count(ARRAY[1]) == 1 && m.count(ARRAY[2]) == 2 &&
//			m.count(ARRAY[3]) == 3 && m.count(ARRAY[0]) == 0);
//	} break; case 99: {
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[3]);
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[3]);
//		m.insert(ARRAY[3]);
//		m.replace(ARRAY[0], ARRAY[3]);
//		assert(m.uniqueSize() == 2 && m.size() == 6 &&
//			m.count(ARRAY[1]) == 1 && m.count(ARRAY[3]) == 5 &&
//			m.count(ARRAY[0]) == 0);
//	} break; case 100: {
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[3]);
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[3]);
//		m.insert(ARRAY[3]);
//		m.replace(ARRAY[3], ARRAY[3]);
//		assert(m.uniqueSize() == 3 && m.size() == 6 &&
//			m.count(ARRAY[0]) == 2 && m.count(ARRAY[1]) == 1 &&
//			m.count(ARRAY[3]) == 3);
//	} break; case 101: {
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[2]);
//		m.insert(ARRAY[3]);
//		m.replace(ARRAY[0], DEFAULT);
//		m.insert(ARRAY[4]);
//		m.erase(ARRAY[2]);
//		m.replace(DEFAULT, ARRAY[5]);
//		assert(m.uniqueSize() == 4 && m.size() == 4 &&
//			m.count(ARRAY[0]) == 0 && m.count(ARRAY[1]) == 1 &&
//			m.count(ARRAY[2]) == 0 && m.count(ARRAY[3]) == 1 &&
//			m.count(ARRAY[4]) == 1 && m.count(ARRAY[5]) == 1 &&
//			m.count(DEFAULT) == 0);
//	} break; case 102: {
//		m.insert(ARRAY[3]);
//		m.insert(ARRAY[2]);
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[3]);
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[4]);
//		m.insert(ARRAY[2]);
//		m.insert(ARRAY[4]);
//		assert(m.countIf('$', ARRAY[2]) == -1);
//	} break; case 103: {
//		m.insert(ARRAY[3]);
//		m.insert(ARRAY[2]);
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[3]);
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[4]);
//		m.insert(ARRAY[2]);
//		m.insert(ARRAY[4]);
//		assert(m.countIf('=', ARRAY[2]) == 2);
//	} break; case 104: {
//		m.insert(ARRAY[3]);
//		m.insert(ARRAY[2]);
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[3]);
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[4]);
//		m.insert(ARRAY[2]);
//		m.insert(ARRAY[4]);
//		assert(m.countIf('<', ARRAY[2]) == 3);
//	} break; case 105: {
//		m.insert(ARRAY[3]);
//		m.insert(ARRAY[2]);
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[3]);
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[4]);
//		m.insert(ARRAY[2]);
//		m.insert(ARRAY[4]);
//		assert(m.countIf('>', ARRAY[2]) == 4);
//	} break; case 106: {
//		m.insert(ARRAY[3]);
//		m.insert(ARRAY[2]);
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[3]);
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[4]);
//		m.insert(ARRAY[2]);
//		m.insert(ARRAY[4]);
//		assert(m.countIf('>', ARRAY[4]) == 0);
//	} break; case 107: {
//		Multiset m2;
//		m2.insert(ARRAY[1]);
//		m2.insert(ARRAY[0]);
//		m2.insert(ARRAY[1]);
//		m.copyIntoOtherMultiset(m2);
//		assert(m2.uniqueSize() == 2 && m2.size() == 3 &&
//			m2.count(ARRAY[0]) == 1 && m2.count(ARRAY[1]) == 2);
//	} break; case 108: {
//		Multiset m2;
//		m2.insert(ARRAY[1]);
//		m2.insert(ARRAY[0]);
//		m2.insert(ARRAY[1]);
//		m2.copyIntoOtherMultiset(m);
//		assert(m.count(ARRAY[0]) == 1 && m.count(ARRAY[1]) == 2);
//	} break; case 109: {
//		Multiset m2;
//		m2.insert(ARRAY[1]);
//		m2.insert(ARRAY[0]);
//		m2.insert(ARRAY[1]);
//		m2.copyIntoOtherMultiset(m);
//		assert(m.uniqueSize() == 2 && m.size() == 3);
//	} break; case 110: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		Multiset m2;
//		m2.insert(ARRAY[1]);
//		m2.insert(ARRAY[0]);
//		m2.insert(ARRAY[1]);
//		m2.insert(ARRAY[2]);
//		m.copyIntoOtherMultiset(m2);
//		assert(m2.uniqueSize() == 3 &&
//			m2.count(ARRAY[0]) == 4 && m2.count(ARRAY[1]) == 3 &&
//			m2.count(ARRAY[2]) == 1);
//	} break; case 111: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[3]);
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[4]);
//		m.insert(ARRAY[3]);
//		Multiset m2;
//		m2.insert(ARRAY[1]);
//		m2.insert(ARRAY[0]);
//		m2.insert(ARRAY[1]);
//		m2.insert(ARRAY[2]);
//		m.copyIntoOtherMultiset(m2);
//		assert(m2.count(ARRAY[0]) == 3 && m2.count(ARRAY[1]) == 2 &&
//			m2.count(ARRAY[2]) == 1 && m2.count(ARRAY[3]) == 2 &&
//			m2.count(ARRAY[4]) == 1);
//	} break; case 112: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[3]);
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[4]);
//		m.insert(ARRAY[3]);
//		Multiset m2;
//		m2.insert(ARRAY[1]);
//		m2.insert(ARRAY[0]);
//		m2.insert(ARRAY[1]);
//		m2.insert(ARRAY[2]);
//		m.copyIntoOtherMultiset(m2);
//		assert(m2.uniqueSize() == 5 && m2.size() == 9);
//	} break; case 113: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		{
//			Multiset m2;
//			m2.insert(ARRAY[2]);
//			m2.insert(ARRAY[3]);
//			m2.insert(ARRAY[1]);
//			m2.insert(ARRAY[1]);
//			m.swap(m2);
//			assert(m.size() == 4 && m.uniqueSize() == 3);
//		}
//	} break; case 114: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[2]);
//		{
//			Multiset m2;
//			m2.insert(ARRAY[2]);
//			m2.insert(ARRAY[3]);
//			m2.insert(ARRAY[1]);
//			m2.insert(ARRAY[1]);
//			m.swap(m2);
//			assert(m.count(ARRAY[1]) == 2 && m.count(ARRAY[2]) == 1 &&
//				m.count(ARRAY[3]) == 1 && m.count(ARRAY[0]) == 0);
//		}
//	} break; case 115: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		{
//			Multiset m2;
//			m2.insert(ARRAY[2]);
//			m2.insert(ARRAY[3]);
//			m2.insert(ARRAY[1]);
//			m2.insert(ARRAY[1]);
//			m.swap(m2);
//			assert(m2.size() == 2 && m2.uniqueSize() == 2);
//		}
//	} break; case 116: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[2]);
//		{
//			Multiset m2;
//			m2.insert(ARRAY[2]);
//			m2.insert(ARRAY[3]);
//			m2.insert(ARRAY[1]);
//			m2.insert(ARRAY[1]);
//			m.swap(m2);
//			assert(m2.count(ARRAY[0]) == 1 && m2.count(ARRAY[1]) == 1 &&
//				m2.count(ARRAY[2]) == 1 && m2.count(ARRAY[3]) == 0);
//		}
//	} break; case 117: {
//		for (int k = 0; k < SPEC_MAX; k++)
//		{
//			assert(m.insert(k));
//			assert(m.insert(k));
//		}
//		assert(m.size() == 2 * SPEC_MAX  &&  m.uniqueSize() == SPEC_MAX);
//	} break; case 118: {
//		for (int k = 0; k < SPEC_MAX; k++)
//			assert(m.insert(k));
//		ItemType x = SPEC_MAX;
//		assert(/*!m.insert(x) &&*/ m.size() == SPEC_MAX  &&
//			m.uniqueSize() == SPEC_MAX && !m.contains(x));
//	} break; case 119: {
//		assert(m.insert(DUMMY));
//		for (int k = 0; k < 10 * SPEC_MAX; k++)
//			assert(m.insert(DUMMY));
//	} break; case 120: {
//		for (int k = 0; k < SPEC_MAX; k++)
//			assert(m.insert(k));
//		assert(!m.insert(SPEC_MAX));
//		m.erase(0);
//		assert(m.insert(SPEC_MAX + 1));
//		assert(!m.insert(SPEC_MAX + 2));
//	} break; case 121: {
//		 This test checked that swap executes the same number of
//		 instructions regardless of the number of items in the Multisets.
//	} break; /* case 122: {
//		const int CAPACITY = 2;
//		Multiset m2(CAPACITY);
//		for (int k = 0; k < CAPACITY; k++)
//			assert(m2.insert(k));
//		assert(!m2.insert(CAPACITY));
//	} break; case 123: {
//		const int CAPACITY = 2;
//		Multiset m2(CAPACITY);
//		for (int k = 0; k < CAPACITY; k++)
//		{
//			assert(m2.insert(k));
//			assert(m2.insert(k));
//		}
//		assert(!m2.insert(CAPACITY));
//	} break; case 124: {
//		const int CAPACITY = SPEC_MAX * 2;
//		Multiset m2(CAPACITY);
//		for (int k = 0; k < CAPACITY; k++)
//			assert(m2.insert(k));
//		assert(!m2.insert(CAPACITY));
//	} break; */ case 125: {
//		 This test checked that the destructor deletes the array of items.
//	} break; case 126: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[2]);
//		{
//			Multiset m2(m);
//			m2.insert(ARRAY[3]);
//			assert(m2.size() == m.size() + 1 &&
//				m2.uniqueSize() == m.uniqueSize() + 1);
//		}
//	} break; case 127: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[2]);
//		{
//			Multiset m2(m);
//			m2.insert(ARRAY[3]);
//			assert(m2.uniqueSize() == 4 && m2.count(ARRAY[0]) == 1 &&
//				m2.count(ARRAY[1]) == 1 && m2.count(ARRAY[2]) == 1 &&
//				m2.count(ARRAY[3]) == 1);
//		}
//	} break; case 128: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		m.insert(ARRAY[2]);
//		{
//			Multiset m2(m);
//			m2.insert(ARRAY[3]);
//			assert(m.uniqueSize() == 3 && m.count(ARRAY[0]) == 1 &&
//				m.count(ARRAY[1]) == 1 && m.count(ARRAY[2]) == 1 &&
//				m.count(ARRAY[3]) == 0);
//		}
//	} break; case 129: {
//		{
//			Multiset m2;
//			m2.insert(ARRAY[0]);
//			m2.insert(ARRAY[1]);
//			Multiset m3(m2);
//			assert(m3.insert(ARRAY[2]));
//		}
//	} break; case 130: {
//		 This test checked that the assignment operator doesn't just
//		 copy a pointer.
//	} break; case 131: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		{
//			Multiset m2;
//			m2.insert(ARRAY[2]);
//			m2.insert(ARRAY[3]);
//			m2.insert(ARRAY[4]);
//			m2 = m;
//			m2.insert(ARRAY[5]);
//			assert(m2.size() == m.size() + 1 &&
//				m2.uniqueSize() == m.uniqueSize() + 1);
//		}
//	} break; case 132: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		{
//			Multiset m2;
//			m2.insert(ARRAY[3]);
//			m2.insert(ARRAY[4]);
//			m2.insert(ARRAY[5]);
//			m2 = m;
//			m2.insert(ARRAY[2]);
//			assert(m2.uniqueSize() == 3 && m2.count(ARRAY[0]) == 1 &&
//				m2.count(ARRAY[1]) == 1 && m2.count(ARRAY[2]) == 1 &&
//				m2.count(ARRAY[3]) == 0);
//		}
//	} break; case 133: {
//		m.insert(ARRAY[0]);
//		m.insert(ARRAY[1]);
//		{
//			Multiset m2;
//			m2.insert(ARRAY[3]);
//			m2.insert(ARRAY[4]);
//			m2.insert(ARRAY[5]);
//			m2 = m;
//			m2.insert(ARRAY[2]);
//			assert(m.uniqueSize() == 2 && m.count(ARRAY[0]) == 1 &&
//				m.count(ARRAY[1]) == 1 && m.count(ARRAY[2]) == 0 &&
//				m.count(ARRAY[3]) == 0);
//		}
//	} break; case 134: {
//		 This test checked that self-assignment works correctly.
//	}
//	}
//}
//
//#define CHECKTYPE(f, t) { auto p = (t)(f); (void)p; }
//
//void thisFunctionWillNeverBeCalled()
//{
//	Multiset();
//	(Multiset(Multiset()));
//	CHECKTYPE(&Multiset::operator=, Multiset& (Multiset::*)(const ItemType&));
//	CHECKTYPE(&Multiset::empty, bool (Multiset::*)() const);
//	CHECKTYPE(&Multiset::size, int  (Multiset::*)() const);
//	CHECKTYPE(&Multiset::uniqueSize, int  (Multiset::*)() const);
//	CHECKTYPE(&Multiset::insert, bool (Multiset::*)(const ItemType&));
//	CHECKTYPE(&Multiset::erase, int  (Multiset::*)(const ItemType&));
//	CHECKTYPE(&Multiset::eraseAll, int  (Multiset::*)(const ItemType&));
//	CHECKTYPE(&Multiset::contains, bool (Multiset::*)(const ItemType&) const);
//	CHECKTYPE(&Multiset::count, int  (Multiset::*)(const ItemType&) const);
//	CHECKTYPE(&Multiset::get, int  (Multiset::*)(int, ItemType&) const);
//	CHECKTYPE(&Multiset::getLeastFrequentValue, bool  (Multiset::*)(ItemType&) const);
//	CHECKTYPE(&Multiset::getSmallestValue, bool  (Multiset::*)(ItemType&) const);
//	CHECKTYPE(&Multiset::getSecondSmallestValue, bool  (Multiset::*)(ItemType&) const);
//	CHECKTYPE(&Multiset::replace, bool  (Multiset::*)(ItemType, ItemType));
//	CHECKTYPE(&Multiset::countIf, int  (Multiset::*)(char, ItemType) const);
//	CHECKTYPE(&Multiset::swap, void (Multiset::*)(Multiset&));
//	CHECKTYPE(&Multiset::copyIntoOtherMultiset, int  (Multiset::*)(Multiset&) const);
//	CHECKTYPE(combine, void(*)(const Multiset&, const Multiset&, Multiset&));
//	CHECKTYPE(subtract, void(*)(const Multiset&, const Multiset&, Multiset&));
//	cout << "Passed" << endl;
//}

void test()
{
	Multiset sms;
	assert(sms.insert("cumin"));
	assert(sms.insert("turmeric"));
	assert(sms.insert("cumin"));
	assert(sms.insert("coriander"));
	assert(sms.insert("cumin"));
	assert(sms.insert("turmeric"));
	assert(sms.size() == 6 && sms.uniqueSize() == 3);
	assert(sms.count("turmeric") == 2);
	assert(sms.count("cumin") == 3);
	assert(sms.count("coriander") == 1);
	assert(sms.count("cardamom") == 0);

	/* Multiset ulms;
            assert(ulms.insert(20));
            assert(ulms.insert(10));
            assert(ulms.insert(20));
            assert(ulms.insert(30));
            assert(ulms.insert(20));
            assert(ulms.insert(10));
            assert(ulms.size() == 6  &&  ulms.uniqueSize() == 3);
            assert(ulms.count(10) == 2);
            assert(ulms.count(20) == 3);
            assert(ulms.count(30) == 1);
            assert(ulms.count(40) == 0);*/
}

int main()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	////cout << "Enter test number: ";
	////int n;
	////cin >> n;
	//for (int i = 1; i <= 134; i++)
	//{
	//	if (i == 122 || i == 123 || i == 124)
	//		continue;
	//	testone(i);
	//}

	//ItemType a[8] = { 2,2,2,8,3,3,9,5 };
	//ItemType b[6] = { 6,3,8,8,5,10 };
	//Multiset ma;
	//for (int n = 0; n < 8; n++)
	//	ma.insert(a[n]);
	//Multiset mb;
	//for (int n = 0; n < 6; n++)
	//	mb.insert(b[n]);

	//Multiset mc;
	//for (int n = 0; n < 5; n++)
	//	mc.insert(a[n]);
	//combine(ma, mb, mc);
	//for (int n = 0; n < mc.uniqueSize(); n++)
	//{
	//	ItemType val;
	//	int count = mc.get(n, val);
	//	cout << val << " count: " << count << endl;
	//}
	//assert(mc.count(6) == 1 && mc.count(3) == 3 && mc.size() == 14 && mc.uniqueSize() == 7);
	//cout << endl;

	//Multiset md;
	//for (int n = 0; n < 5; n++)
	//	md.insert(a[n]);
	//subtract(ma, mb, md);
	//for (int n = 0; n < md.uniqueSize(); n++)
	//{
	//	ItemType val;
	//	int count = md.get(n, val);
	//	cout << val << " count: " << count << endl;
	//}
	//assert(md.count(9) == 1 && md.count(2) == 3 && md.size() == 5 && md.uniqueSize() == 3);
	//cout << endl;

	//combine(ma, ma, ma);
	//for (int n = 0; n < ma.uniqueSize(); n++)
	//{
	//	ItemType val;
	//	int count = ma.get(n, val);
	//	cout << val << " count: " << count << endl;
	//}
	//assert(ma.count(8) == 2 && ma.count(2) == 6 && ma.size() == 16 && ma.uniqueSize() == 5);
	//cout << endl;

	//subtract(mb, mb, mb);
	//for (int n = 0; n < mb.uniqueSize(); n++)
	//{
	//	ItemType val;
	//	int count = mb.get(n, val);
	//	cout << val << " count: " << count << endl;
	//}
	//assert(mb.size() == 0 && mb.uniqueSize() == 0 && mb.count(8) == 0);
	//cout << endl;

	//Multiset ma1;
	//for (int n = 0; n < 8; n++)
	//	ma1.insert(a[n]);
	//Multiset mb1;
	//for (int n = 0; n < 6; n++)
	//	mb1.insert(b[n]);
	//Multiset mc1;
	//for (int n = 0; n < 6; n++)
	//	mc1.insert(b[n]);

	//combine(ma1, mb1, mb1);
	//assert(mb1.count(10) == 1 && mb1.count(8) == 3 && mb1.size() == 14 && mb1.uniqueSize() == 7);

	//subtract(ma1, mc1, mc1);
	//assert(mc1.count(9) == 1 && mc1.count(2) == 3 && mc1.size() == 5 && mc1.uniqueSize() == 3);
	//
	//thisFunctionWillNeverBeCalled();
	test();

	cout << "Passed" << endl;

	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();
}