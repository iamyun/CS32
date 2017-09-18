//
//#include <iostream>
//#include <string>
//#include "StudentMultiset.h"
//using namespace std;
//
//StudentMultiset::StudentMultiset()
//// Create an empty student multiset.
//{
//	id_size = 0;
//	student_size = 0;
//}
//
//bool StudentMultiset::add(unsigned long id)
//// Add a student id to the StudentMultiset.  Return true if and only
//// if the id was actually added.
//{
//	bool contained = student.contains(id);
//	if (student.insert(id))
//	{
//		if (!contained)
//		{
//			id_size++;
//		}
//		student_size++;
//		return true;
//	}
//	return false;
//
//}
//
//int StudentMultiset::size() const
//// Return the number of items in the StudentMultiset.  If an id was
//// added n times, it contributes n to the size.
//{
//	return student_size;
//}
//
//void StudentMultiset::print() const
//// Print to cout every student id in the StudentMultiset one per line;
//// print as many lines for each id as it occurs in the StudentMultiset.
//{
//	ItemType id;
//	for (int i = 0; i < id_size; i++)
//	{
//		int count = student.get(i, id);
//		for (int j = 0; j < count; j++)
//			cout << id << endl;
//	}
//}
