
#include <iostream>
#include <string>
#include "newMultiset.h"
using namespace std;

Multiset::Multiset()   // Create an empty multiset.
{
	elem_size = 0;
	set_size = 0;
	set_cap = DEFAULT_MAX_ITEMS;
	elem = new item[DEFAULT_MAX_ITEMS];		//create dynamic allocated array that can hold DEFAULT_MAX_ITEMS items;
}

Multiset::Multiset(int cap)   // Create an empty multiset.
{
	if (cap < 0)
	{
		cout << "Maximum capacity of multiset must be positive" << endl;
		exit(1);
	}
	elem_size = 0;
	set_size = 0;
	set_cap = cap;
	elem = new item[set_cap];	//create dynamic allocated array that can hold cap items;
}

Multiset::Multiset(const Multiset &src)	//copy constructor
{
	elem_size = src.elem_size;
	set_size = src.set_size;
	set_cap = src.set_cap;
	elem = new item[set_cap];
	for (int i = 0; i < elem_size; i++)	//copy all values and counts from the source class to the new class
	{
		elem[i].value = src.elem[i].value;
		elem[i].count = src.elem[i].count;
	}
}

Multiset& Multiset::operator= (const Multiset &src)	//assignment operator
{
	if (&src == this)	//if it's the class itself, do nothing and return
		return(*this);
	delete[] elem;	//delete the existing array
	elem_size = src.elem_size;
	set_size = src.set_size;
	set_cap = src.set_cap;
	elem = new item[set_cap];	//create a new dynamic allocated array of item type
	for (int i = 0; i < elem_size; i++)	////copy all values and counts from the source class to the new class
	{
		elem[i].value = src.elem[i].value;
		elem[i].count = src.elem[i].count;
	}
	return(*this);
}

Multiset::~Multiset()		//destructor;
{
	if (elem != nullptr)
		delete[] elem;
	//elem = nullptr;
}

bool Multiset::empty() const  // Return true if the multiset is empty, otherwise false.
{
	if (set_size <= 0)
	{
		return true;
	}
	return false;
}

int Multiset::size() const
// Return the number of items in the multiset.  For example, the size
// of a multiset containing "cumin", "cumin", "cumin", "turmeric" is 4.
{
	return set_size;
}

int Multiset::uniqueSize() const
// Return the number of distinct items in the multiset.  For example,
// the uniqueSize of a multiset containing "cumin", "cumin", "cumin",
// "turmeric" is 2.
{
	return elem_size;
}

bool Multiset::insert(const ItemType& value)
// Insert value into the multiset.  Return true if the value was
// actually inserted.  Return false if the value was not inserted
// (perhaps because the multiset has a fixed capacity and is full).
{
	for (int i = 0; i < elem_size; i++)	//if value already exist in the set, add 1 to the original count of value
	{
		if (elem[i].value == value)
		{
			elem[i].count++;
			set_size++;
			return true;
		}
	}

	if (elem_size < set_cap)	//if value is new to the set, increase unique size of the size by 1 after adding the new value, set count of value to 1
	{
		elem[elem_size].value = value;
		elem[elem_size].count = 1;
		elem_size++;
		set_size++;
		return true;
	}

	return false;	//if it's a new element but already reach maximum capacity of set
}

int Multiset::erase(const ItemType& value)
// Remove one instance of value from the multiset if present.
// Return the number of instances removed, which will be 1 or 0.
{
	for (int i = 0; i < elem_size; i++)
	{
		if (elem[i].value == value)
		{
			if (elem[i].count <= 1)	
			// if it's the last instance of value in the set, move the last element in the set to its position and decrement the unique size by 1
			{
				elem[i].value = elem[elem_size - 1].value;
				elem[i].count = elem[elem_size - 1].count;
				elem_size--;
				set_size--;
				return 1;
			}
			else   //else, simply decrement the count of the value by one
			{
				elem[i].count--;
				set_size--;
				return 1;
			}
		}
	}
	return 0;	//if element not found, return 0
}

int Multiset::eraseAll(const ItemType& value)
// Remove all instances of value from the multiset if present.
// Return the number of instances removed.
{
	int numRomoved = 0;
	for (int i = 0; i < elem_size; i++)
	{
		if (elem[i].value == value)
		{
			numRomoved = elem[i].count;		//total items removed should equal to the count of the element
			set_size -= numRomoved;		//total size of set decrease by the count of the element
			elem[i].value = elem[elem_size - 1].value;	//replace the element with the last element of the set
			elem[i].count = elem[elem_size - 1].count;
			elem_size--;	//decrement the unique size of set by one
			return numRomoved;
		}
	}
	return numRomoved;
}

bool Multiset::contains(const ItemType& value) const
// Return true if the value is in the multiset, otherwise false.
{
	for (int i = 0; i < elem_size; i++)		//loop through the entire set to check if any element's value match with value
	{
		if (elem[i].value == value)
			return true;
	}
	return false;
}

int Multiset::count(const ItemType& value) const	
// Return the number of instances of value in the multiset.
{
	for (int i = 0; i < elem_size; i++)	
	{
		if (elem[i].value == value)
			return elem[i].count;
	}
	return 0;
}

int Multiset::get(int i, ItemType& value) const
// If 0 <= i < uniqueSize(), copy into value an item in the
// multiset and return the number of instances of that item in
// the multiset.  Otherwise, leave value unchanged and return 0.
// (See below for details about this function.)
{
	if (0 <= i && i < uniqueSize())
	{
		value = elem[i].value;	//copy the value of the element at i position to value
		return elem[i].count;	//return the number of instances of that item
	}
	return 0;	//return 0 if position is out of bound
}

bool Multiset::getLeastFrequentValue(ItemType &value) const
// If there exists a single item that has the least number of instances in the multiset, 
// then copy into value that item in the multiset and return true.
// However, if there exist more than 1 item that have the least number of instances in the multiset,
// then do not copy into value any item in the multiset and return false. In other words, value should remain unchanged.
// If there's no item in the multiset, return false.
{
	if (empty())	//if set is empty, return false
		return false;

	int leastCount = set_size;	//initialize least count to the total count of the set
	int timesLFV = 0;
	int posLFV = 0;

	for (int i = 0; i < elem_size; i++)
	{
		if (elem[i].count < leastCount)	//compare each element's count with current least frequent value's count, update least count if found new least count
		{
			leastCount = elem[i].count;
			timesLFV = 1;
			posLFV = i;
		}
		else if (elem[i].count == leastCount)	
		//if found element have the same count as the current least count, increase numbers of elements in the set that with least count
		{
			timesLFV++;
		}
	}

	if (timesLFV != 1)	//if more than one element have least number of instances in the set, return false
		return false;

	value = elem[posLFV].value;		//if there's a single element with least count, change value to the least frequent value and return true
	return true;
}

bool Multiset::getSmallestValue(ItemType &value) const
// If there exists a value that is the smallest value among all the values in the multiset, 
// then copy into value that item in the multiset and return true
// Otherwise, return false.
// For both unsigned long and string data type, the lower value can be found by using less than operator (<).
// For example, 10 is smaller than 20, so 10 < 20 is true.
// "ABCDE" is smaller than "XYZ", so "ABCDE" < "XYZ" is true.
{
	if (elem_size < 1)	//return flase if there is less than one element in the set
		return false;

	ItemType tempSV = elem[0].value;	//initialize smallest value to value of first element in the set
	int posSV = 0;

	for (int i = 0; i < elem_size; i++)	//compare each element's value with current smallest value, update smallest value if found new smallest value
	{
		if (elem[i].value < tempSV)
		{
			tempSV = elem[i].value;
			posSV = i;
		}
	}

	value = elem[posSV].value;
	return true;
}

bool Multiset::getSecondSmallestValue(ItemType &value) const
// Similar to getSmallestValue(), but this time you need to find the second smallest value.
// If there exists a value that is the 2nd smallest value among all the values in the multiset,
// then copy into value that item in the multiset and return true.
// Otherwise, return false.
// Please note that you cannot use any sorting algorithm to sort the multiset.
{
	if (elem_size < 2)	//if there are less than 2 element in the set, there's no second smallest value, so return false
		return false;

	ItemType tempSV = elem[0].value;	//initialize smallest value as first element in multiset
	ItemType tempSecV = elem[1].value;	//initialize second smallest value as the second element in multiset
	int posSV = 0;	//smallest value's location in the set 
	int posSecV = 1;	//secpnd smallest value's location in the set 

	for (int i = 0; i < elem_size; i++)
	{
		if (elem[i].value <= tempSecV && elem[i].value < tempSV)	
		//if the value if smaller than both current second smallest and the current smallest value
		//change second smallest value to the current smallest value
		//and change the current smallest value to the new found smallest value
		{
			tempSecV = tempSV;
			posSecV = posSV;
			posSV = i;
			tempSV = elem[i].value;
		}
		else if (elem[i].value > tempSecV && elem[i].value <= tempSV)
		//if the value is greater than the current second smallest value, but smaller than the current smallest value
		//this means the current second smallest value the smallest among the three, while the current smallest value is the biggest
		//and the new found value is second smallest.
		//Therefore, swap smallest value with second smallest value, and update second smallest value to the new found value
		{
			tempSV = tempSecV;
			posSV = posSecV;
			posSecV = i;
			tempSecV = elem[i].value;
		}
		else if (elem[i].value < tempSecV && elem[i].value > tempSV)
		//if the value is greater than the current smallest value but smaller than the current second smallest value
		//update the second smallest value to the new found value
		{
			tempSecV = elem[i].value;
			posSecV = i;
		}
	}

	if (tempSecV == tempSV)	//if the second smallest value happen to be the same as the smallest value, return false
		return false;

	value = elem[posSecV].value;	//otherwise, return the second smallest value
	return true;
}

bool Multiset::replace(ItemType original, ItemType new_value)
// Replace the item that has the value equal to original by the new value new_value.
// For example, replace("ABCDE","XYZ") will search the multiset for the item "ABCDE" and replace all occurrences of "ABCDE" as "XYZ".
// If the replacement is successful, then return true.
// If there is no item to be replaced, then return false.
{
	for (int i = 0; i < elem_size; i++)
	{
		if (elem[i].value == original)	//find the element in set that has original value
		{
			int pos = find(*this, new_value);
			if (pos == -1)
				elem[i].value = new_value;	//change the value to new_value
			else
			{
				elem[pos].count += elem[i].count;
				elem[i].value = elem[elem_size-1].value;
				elem[i].count = elem[elem_size - 1].count;
				elem_size--;
			}
			return true;
		}
	}
	return false;	//if original value not found, return false
}

int Multiset::countIf(char op, ItemType value) const
// Count the number of items that the item is greater than, less than, or equal to value.
// For example: 
// countIf('>',100) returns the number of items in multiset in which the item is greater than 100.
// countIf('=',"ABC") returns the number of items in multiset in which the item is equal to "ABC".
// countIf('<',50) returns the number of items in multiset in which the item is less than 50.
// If op is a character other than '>','=', and '<', then return -1.		  
{
	int numItem = 0;
	switch (op)
	//get to the case with the correct op
	//go through the set to find elements with values that are >, =, or < than value, depending on what op was entered
	//add the count of the element that qualifies for op to get the total instances of items that qualifies for op
	{
	case '>':
		for (int i = 0; i < elem_size; i++)
		{
			if (elem[i].value > value)
				numItem += elem[i].count;
		}
		return numItem;
		break;
	case '=':
		for (int i = 0; i < elem_size; i++)
		{
			if (elem[i].value == value)
				numItem += elem[i].count;
		}
		return numItem;
		break;
	case '<':
		for (int i = 0; i < elem_size; i++)
		{
			if (elem[i].value < value)
				numItem += elem[i].count;
		}
		return numItem;
		break;
	default:
		return -1;	//if op is not >, =, or < return -1
	}
}

void Multiset::swap(Multiset& other)
// Exchange the contents of this multiset with the other one.
{
	int tempElem_size = elem_size;
	int tempSet_size = set_size;
	int temp_cap = set_cap;

	elem_size = other.elem_size;
	set_size = other.set_size;
	set_cap = other.set_cap;

	other.elem_size = tempElem_size;
	other.set_size = tempSet_size;
	other.set_cap = temp_cap;

	item* tempElem = elem;
	elem = other.elem;
	other.elem = tempElem;
}

void Multiset::copyIntoOtherMultiset(Multiset &other) const
// Insert all the items into the multiset in other.		
{
	for (int i = 0; i < elem_size; i++)
	{
		int pos = find(other, elem[i].value);
		if (pos != -1)
		{
			other.elem[pos].count += elem[i].count;
			other.set_size += elem[i].count;
		}
		else if (pos == -1 && other.elem_size < other.set_cap)
		{
			other.elem[other.elem_size].value = elem[i].value;
			other.elem[other.elem_size].count = elem[i].count;
			other.elem_size++;
			other.set_size += elem[i].count;
			continue;
		}
		else if (pos == -1 && other.elem_size >= other.set_cap)
		{
			continue;
		}
	}
}

int Multiset::find(const Multiset &set, const ItemType &value) const
{
	int pos = -1;
	for (int i = 0; i < set.elem_size; i++)
	{
		if (set.elem[i].value == value)
			pos = i;
	}
	return pos;
}