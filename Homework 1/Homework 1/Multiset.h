//
//#ifndef MULTISET
//
//#define MULTISET
//
//#include <string>
//typedef unsigned long ItemType;
//const int DEFAULT_MAX_ITEMS = 200;
//
//class Multiset
//{
//public:
//	Multiset();   
//
//	bool empty() const;  
//
//	int size() const;
//	
//	int uniqueSize() const;
//	
//	bool insert(const ItemType& value);
//	
//	int erase(const ItemType& value);
//	
//	int eraseAll(const ItemType& value);
//	
//	bool contains(const ItemType& value) const;
//	
//	int count(const ItemType& value) const;
//	
//	int get(int i, ItemType& value) const;
//	
//	bool getLeastFrequentValue(ItemType &value) const;
//	
//	bool getSmallestValue(ItemType &value) const;
//	
//	bool getSecondSmallestValue(ItemType &value) const;
//	
//	bool replace(ItemType original, ItemType new_value);
//	
//	int countIf(char op, ItemType value) const;
//	
//	void swap(Multiset& other);
//	
//	void copyIntoOtherMultiset(Multiset &other) const;
//	
//private:
//	struct item
//	{
//		ItemType value;
//		int count;
//	};
//
//	int find(const Multiset& set, const ItemType &value) const;
//	
//	item elem[DEFAULT_MAX_ITEMS];
//	int elem_size;	//count for unique items in the set
//	int set_size;	//count for total items in the set
//};
//
//#endif
