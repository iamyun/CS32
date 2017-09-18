#ifndef MULTISET_INCLUDED
#define MULTISET_INCLUDED

#include <string>
typedef std::string ItemType;

class Multiset
{
public:
	Multiset();               // Create an empty multiset.

	Multiset(const Multiset& other);	//copy Constructor

	~Multiset();				//destructor

	Multiset& operator=(const Multiset& other);	//assignment operator

	bool empty() const;  // Return true if the multiset is empty, otherwise false.

	int size() const;
	// Return the number of items in the multiset.  For example, the size
	// of a multiset containing "cumin", "cumin", "cumin", "turmeric" is 4.

	int uniqueSize() const;
	// Return the number of distinct items in the multiset.  For example,
	// the uniqueSize of a multiset containing "cumin", "cumin", "cumin",
	// "turmeric" is 2.

	bool insert(const ItemType& value);
	// Insert value into the multiset.  Return true if the value was
	// actually inserted.  Should always return true since Linked List 
	//has not maximum capacity, should always be able to insert more

	int erase(const ItemType& value);
	// Remove one instance of value from the multiset if present.
	// Return the number of instances removed, which will be 1 or 0.

	int eraseAll(const ItemType& value);
	// Remove all instances of value from the multiset if present.
	// Return the number of instances removed.

	bool contains(const ItemType& value) const;
	// Return true if the value is in the multiset, otherwise false.

	int count(const ItemType& value) const;
	// Return the number of instances of value in the multiset.

	int get(int i, ItemType& value) const;
	// If 0 <= i < uniqueSize(), copy into value an item in the multiset
	// and return the number of instances of that item in the multiset.
	// Otherwise, leave value unchanged and return 0.

	bool getLeastFrequentValue(ItemType& value) const;
	// If there exists a single item that has the least number of instances in the multiset, 
	// then copy into value that item in the multiset and return true.
	// However, if there exist more than 1 item that have the least number of instances in the multiset,
	// then do not copy into value any item in the multiset and return false. In other words, value should remain unchanged.
	// If there's no item in the multiset, return false.

	bool getSmallestValue(ItemType& value) const;
	// If there exists a value that is the smallest value among all the values in the multiset, 
	// then copy into value that item in the multiset and return true
	// Otherwise, return false.
	// For both unsigned long and string data type, the lower value can be found by using less than operator (<).
	// For example, 10 is smaller than 20, so 10 < 20 is true.
	// "ABC" is smaller than "XYZ", so "ABC" < "XYZ" is true.

	bool getSecondSmallestValue(ItemType& value) const;
	// Similar to getSmallestValue(), but this time you need to find the second smallest value.
	// If there exists a value that is the 2nd smallest value among all the values in the multiset,
	// then copy into value that item in the multiset and return true.
	// Otherwise, return false.
	// Please note that you cannot use any sorting algorithm to sort the multiset.

	bool replace(ItemType original, ItemType new_value);
	// Replace the item that has the value equal to original by the new value
	// new_value.  For example, replace("ABC","XYZ") will search the multiset
	// for the item "ABC" and replace all occurrences of "ABC" as "XYZ".
	// If the replacement is successful, then return true.  If there is no
	// item to be replaced, then return false.

	int countIf(char op, ItemType value) const;
	// Count the number of items that the item is greater than, less than, or
	// equal to value.  For example:  countIf('>',100) returns the number of
	// items in multiset in which the item is greater than 100.

	void swap(Multiset& other);
	// Exchange the contents of this multiset with the other one.

	void copyIntoOtherMultiset(Multiset& other) const;
	// Insert all the items into the multiset in other.

private:

	// Since this structure is used only by the implementation of the
	// Multiset class, we'll make it private to Multiset.

	struct Node
	{
		ItemType m_value;
		int      m_count;
		Node*	 prev;	//points to the previous Node in multiset
		Node*	 next;	//points to the next Node in multiset
	};					
	Node* head;		//points to the first Node in multiset 
	Node* tail;		//points to the last Node in Multiset
	int  m_uniqueSize;               // how many distinct items in the multiset
	int  m_size;                     // total number of items in the multiset

	Node* find(const ItemType& value) const;
	// Return pointer points to the node in multiset whose m_value == value if there is
	// one, else return nullptr

	bool insertMany(const ItemType& value, int nToInsert, int& uniqueSize);
	// Insert value with (additional) count nToInsert using (and possibly
	// updating) uniqueSize as the number of distinct existing items, and
	// return true.

	int doErase(const ItemType& value, bool all);
	// Remove one or all instances of value from the multiset if present,
	// depending on the second parameter.  Return the number of instances
	// removed.

	void exchange(int& a, int& b);	//exchange the value of a and b
};

// Inline implementations

void combine(const Multiset& ms1, const Multiset& ms2, Multiset& result);
void subtract(const Multiset& ms1, const Multiset& ms2, Multiset& result);

inline
int Multiset::size() const
{
	return m_size;
}

inline
int Multiset::uniqueSize() const
{
	return m_uniqueSize;
}

inline
bool Multiset::empty() const
{
	return size() == 0;
}

inline
int Multiset::erase(const ItemType& value)
{
	return doErase(value, false);
}

inline
int Multiset::eraseAll(const ItemType& value)
{
	return doErase(value, true);
}

inline
bool Multiset::contains(const ItemType& value) const
{
	return find(value) != nullptr;
}

#endif // MULTISET_INCLUDED

