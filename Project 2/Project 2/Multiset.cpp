#include "Multiset.h"

void Multiset::exchange(int& a, int& b)
//swap the value of a and b
{
	int t = a;	//create temporary int to store the value of a for later use
	a = b;
	b = t;
}

Multiset::Multiset()
	: m_uniqueSize(0), m_size(0)	//initialize m_uniqueSize and m_size to 0
{
	//create empty multiset with head and tail equal to nullptr
	head = nullptr;		
	tail = nullptr;
}

Multiset::Multiset(const Multiset& other)
	: m_uniqueSize(other.m_uniqueSize), m_size(other.m_size)	//copy m_uniqueSize and m_size of other set to the new set
{
	//trace through the entire multiset linked list, starting at the head
	Node* pos = other.head;		
	while (pos != nullptr)
	//break when reach the end of multiset linked list
	{
		//create new Node to copy what's in the same position of other multiset
		Node* nPos = new Node;
		nPos->m_value = pos->m_value;
		nPos->m_count = pos->m_count;
		if (pos == other.head)	
		//if this is the first Node to be copied, set next to nullptr
		//set the current Node as head
		{
			nPos->prev = nullptr;
			head = nPos;
		}
		else
		//otherwise, the original tail's next points to the latest added Node
		//the lastest added Node's previous points to the original tail
		{
			tail->next = nPos;
			nPos->prev = tail;
		}
		nPos->next = nullptr;	//the new Node's next will be a node pointer
		tail = nPos;	//set tail points to the newest added Node
		pos = pos->next;	//move on to the next Node in the other Multiset
	}
}

Multiset::~Multiset()
{
	Node* pos = head;	//starting at the head of the multiset
	while (pos != nullptr)
		//until reach the end of multiset
	{
		Node* nx = pos->next;	//get the next Node in the set
		delete pos;	//delete the current Node
		pos = nx;	//move on to the next Node
	}
}

Multiset& Multiset::operator=(const Multiset& rhs)
{
	if (this != &rhs)	//if the rhs set is not the same as the original set
	{
		Multiset temp(rhs);	//create temporary Multiset and copy what's in the rhs set to temporary set using copy constructor
		swap(temp);		//swap what's in the current set with the temporary set
	}//when if loop end, destructor of temporary set is called and temp is deleted
	return *this;	//always return the this pointer
}

bool Multiset::insert(const ItemType& value)
{
	insertMany(value, 1, m_uniqueSize);	//insert one value to the set
	m_size++;	//increment set size by one
	return true;	//because there's not maximum capacity for linked list, always return true
}

int Multiset::count(const ItemType& value) const
{
	Node* pos = find(value);	//find the position of the value
	return pos == nullptr ? 0 : pos->m_count;	//if not found (find returned nullptr), return 0; if found, return the count of that value
}

int Multiset::get(int i, ItemType& value) const
{
	if (i < 0 || i >= m_uniqueSize)	//return 0 if position looking for is out of bound
		return 0;

	Node* pos = head;
	if (i < (m_uniqueSize/2))
	//if position is closer to the head, move down from the head to find it
	{
		int n = 0;
		while (n != i)
		{
			pos = pos->next;
			n++;
		}
	}
	else
	//if position is closer to the tail, move up from the tail to find it
	{
		pos = tail;
		int n = m_uniqueSize-1;
		while (n != i)
		{
			pos = pos->prev;
			n--;
		}
	}
	value = pos->m_value;	//set value to the founded Node's value
	return pos->m_count;	//return the count of that value
}

bool Multiset::getLeastFrequentValue(ItemType& value) const
{
	if (m_uniqueSize == 0)	//if the set is empty, there's no least frequent value
		return false;

	// Start by assuming head points to Node that has the unique most frequent value

	Node* posLeastFrequent = head;
	bool uniqueLeastFrequent = true;

	// See if any other value is the most frequent
	Node* poss = head->next;
	while (poss != nullptr)
	{
		int diff = (poss->m_count - posLeastFrequent->m_count);
		if (diff == 0)  // most frequent value, but not unique
			uniqueLeastFrequent = false;
		else if (diff < 0)  // a new unique least frequent value
		{
			posLeastFrequent = poss;	//update position of the new unique most frequent value
			uniqueLeastFrequent = true;
		}
		poss = poss->next;	//move on to check the next one
	}

	// Set value and return true only if the most frequent value is unique

	if (uniqueLeastFrequent)
		value = posLeastFrequent->m_value;
	return uniqueLeastFrequent;
}

bool Multiset::getSmallestValue(ItemType& value) const
{
	if (m_uniqueSize == 0)	//if set is empty, no smallest value, return false
		return false;
	Node* posSmallest = head;	//assume head points to Node that has the smallest value
	Node* poss = head->next;	//check the other ones and compare with the current smallest value
	while (poss != nullptr)
	{
		if (poss->m_value < posSmallest->m_value)	//if found new smallest value
			posSmallest = poss;	//update the smallest value
		poss = poss->next;
	}
	value = posSmallest->m_value;	//set value to the smallest value
	return true;
}

bool Multiset::getSecondSmallestValue(ItemType& value) const
{
	if (m_uniqueSize < 2)	//if set has less than 2 Nodes, there's no second smallest value, return false
		return false;

	// posSmallest points to the smallest seen so far
	// posSecondSmallest points to the second smallest seen so far
	// Start by assuming they're in positions 0 and 1 (or 1 and 0).
	Node* posSmallest = head;
	Node* posSecondSmallest = head->next;
	if (posSmallest->m_value > posSecondSmallest->m_value)
	//if posSmallest actually points to Node with bigger value than posSecondSmallest does
	//swap where posSmalelst and posSecondSmallest points to
	{
		Node* t = posSecondSmallest;
		posSecondSmallest = posSmallest;
		posSmallest = t;
	}

	//check value other than the first node and second node
	Node* poss = head->next->next;
	while(poss!=nullptr)
	{
		const ItemType& v = poss->m_value;
		if (v < posSmallest->m_value)  // if found new smallest value so far
		{
			posSecondSmallest = posSmallest;  // old smallest now second smallest
			posSmallest = poss;
		}
		else if (v < posSecondSmallest->m_value)  // if found second smallest so far
			posSecondSmallest = poss;
		poss = poss->next;
	}

	// Set value to second smallest

	value = posSecondSmallest->m_value;
	return true;
}

bool Multiset::replace(ItemType original, ItemType new_value)
{
	Node* posOriginal = find(original);
	if (posOriginal == nullptr)  // no occurrence of original
		return false;
	Node* posNew = find(new_value);
	if (posNew == nullptr)  // new_value not already present?
		posOriginal->m_value = new_value;
	else if (posNew != posOriginal)  // new_value present and distinct from original?
	{
		// Absorb original count into new_value count
		// then eliminate the original

		int count = doErase(original, true);
		posNew->m_count += count;
		m_size += count;	//because doErase decremented the size of multiset, need to add it back so the set size is unchanged.
	}
	return true;
}

int Multiset::countIf(char op, ItemType value) const
{
	//check of op received is a valid op
	if (op != '<'  &&  op != '>'  &&  op != '=')
		return -1;
	int count = 0;
	Node* pos = head;
	while (pos != nullptr)
	{
		bool meetsCriterion = (op == '<' ? pos->m_value < value :
			op == '>' ? pos->m_value > value :
			pos->m_value == value);
		if (meetsCriterion)	//if meet criteria, increment count 
			count += pos->m_count;
		pos = pos->next;
	}
	return count;
}

void Multiset::swap(Multiset& other)
{
	// Swap the original head and tail pointers with other's head and tail pointer.

	Node* tempHead = head;
	Node* tempTail = tail;
	head = other.head;
	tail = other.tail;
	other.head = tempHead;
	other.tail = tempTail;


	// Swap uniqueSize and size.

	exchange(m_uniqueSize, other.m_uniqueSize);
	exchange(m_size, other.m_size);
}

void Multiset::copyIntoOtherMultiset(Multiset& other) const
{
	//starting from the head, insert all items in current set to other set
	Node* pos = head;
	while (pos != nullptr)
	{
		other.m_size += pos->m_count;	//increment set size
		if (!other.insertMany(pos->m_value, pos->m_count, other.m_uniqueSize))	//insert current set's Node to other set
			continue;  
		pos = pos->next;
	}
}

Multiset::Node* Multiset::find(const ItemType& value) const
{
	//one pointer start from the head, one start from the tail to find the value we are looking for
	Node *p;
	p = head;
	while (p != nullptr)	//end when both head and tail go through the entire set
	{
		if (p->m_value == value)
			return p;
		else
			p = p->next;
	}
	return nullptr; //if value is not found in the set, return nullptr
}

bool Multiset::insertMany(const ItemType& value, int nToInsert, int& uniqueSize)
{
	Node* pos = find(value);

	if (pos != nullptr)  // found
		pos->m_count += nToInsert;	//simply add the count
	else	// if not found
	{
		//insert new value to the top
		Node* first;
		first = new Node;
		first->m_value = value;
		first->m_count = nToInsert;
		first->prev = nullptr;	//set previous of new Node to nullptr since it's going to be the head
		if (uniqueSize > 0)	//if this is not the first element to be added to the set
		{
			first->next = head;		//set new Node's next to point to the current head
			head->prev = first;		//set the current head's previous to point to the new Node
		}
		else	//if it is the first Node to be added to the set
		{
			first->next = nullptr;	//new Node's next will be nullptr because there's no other Node to connect to
			tail = first;	//tail will also be the new Node becuase that's the only Node
		}
		head = first;	//set head to point to new Node
		uniqueSize++;	//increase the unique size of multiset
	}
	return true;
}

int Multiset::doErase(const ItemType& value, bool all)
{
	Node* pos = find(value);

	if (pos == nullptr)  // not found
		return 0;

	// If erasing one, and there are more than one, just decrement

	if (!all  &&  pos->m_count > 1)
	{
		pos->m_count--;
		m_size--;
		return 1;
	}

	// If erasing all, or erasing one whose count is 1
	int nErased = pos->m_count;
	if (pos->prev == nullptr && pos->next == nullptr)	
	//if this Node is the only Node in the set
	//delete it and set both head and tail to nullptr
	{
		delete pos;
		head = nullptr;
		tail = nullptr;
	}
	else if (pos->next != nullptr && pos->prev != nullptr)
	//if Node is somewhere between the head and tail
	//its next's previous will now be its previous
	//and it's previous's next will now be its next
	//then delete the Node
	{
		Node* replace = pos->next;
		Node* pv = pos->prev;
		replace->prev = pv;
		pv->next = replace;
		delete pos;
	}
	else if (pos->next == nullptr)
	//if the Node is the tail of the Multiset
	//its previous's next will be nullptr, and tail will now be its previous
	{
		Node* pv = pos->prev;
		pv->next = nullptr;
		tail = pv;
		delete pos;
	}
	else if (pos->prev == nullptr)
	//if the Node is the head of the Multiset
	//its next's previous will be nullptr, and the head will now be it's next
	{
		Node* replace = pos->next;
		replace->prev = nullptr;
		head = replace;
		delete pos;
	}
	m_size -= nErased;	//decrease the set size
	m_uniqueSize--;		//decrease the unique size
	return nErased;
}

void combine(const Multiset& ms1, const Multiset& ms2, Multiset& result)
{
	Multiset temp = ms1;	//copy ms1 to temporary Multiset 
	ms2.copyIntoOtherMultiset(temp);	//copy ms2 to temp (combine ms1 and ms2)
	result = temp;	//copy temp to result and temp will be destructed as it goes out of scope
}

void subtract(const Multiset& ms1, const Multiset& ms2, Multiset& result)
{
	Multiset temp;	//create empty temp Multiset
	for (int i = 0; i < ms1.uniqueSize(); i++)
	{
		ItemType val;
		int count1 = ms1.get(i, val);	//find count of each value in ms1
		int count2 = ms2.count(val);	//found count of the same value in ms2
		int diff = count1 - count2;
		if (diff > 0)	//insert the value into temp only if value has more count in ms1 than ms2
		{
			int n = 0;
			while (n < diff)
			{
				temp.insert(val);
				n++;
			}
		}
	}
	result = temp;	//copy temp to result 
}