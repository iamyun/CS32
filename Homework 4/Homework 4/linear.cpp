#include <iostream>
#include <cctype>
using namespace std;

// Return true if any of the chars in the array is upper-case, false
// otherwise.
bool anyUppercase(const char a[], int n)	
{
	if (n <= 0)
		return false;

	//if the first character of the array is upper case, return true
	if (isupper(a[0]))
		return true;

	return anyUppercase(a+1, n - 1);	
	//keep checking the first element in the array 
	//until it reach the last element or find the upper case element
}

// Return the number of upper-case chars in the array.
int countUppercase(const char a[], int n)
{ 
	if (n <= 0)	//stop when there's no more element in the array to count
		return 0;
	int count = countUppercase(a + 1, n - 1);
	if (isupper(a[0]))	//starting from the back, count back up. Whenever there's an upper case, increment the ocunt
		++count;
	return count;
}

// Return the subscript of the first upper-case char in the array.
// If no element is upper-case, return -1.
int firstUppercase(const char a[], int n)
{
	if (n <= 0)		//if reach end and still no upper case, return -1
		return -1;

	if (isupper(a[0]))	//of the first one is upper case, return 0
		return 0;

	int firstUp = firstUppercase(a + 1, n - 1);

	if (firstUp == -1)
		return -1;
	else return firstUp+1;	//once the first upper case is found, keep adding one till it reach the beginning of the array again
							//which would return the subscript of that element
}

// Return the subscript of the least char in the array (i.e.,
// the smallest subscript m such that there is no k for which
// a[k] < a[m].)  If the array has no elements to examine, return -1.
int indexOfLeast(const char a[], int n)
{
	if (n <= 0)
		return -1;
	
	if (n == 1)	//stop when there's only one element in the array
		return 0;

	//indexOfLeast return position of the least char in the array without the first element in the array
	//add 1 will give least the position of the least char with the first element in the array
	int least = indexOfLeast(a + 1, n - 1) + 1;

	//if the first one is the array is less than least, just return 0
	//else, just return least
	if (a[0] < a[least])
		return 0;
	else return least;
}

//int main()
//{
//	char a1[1] = "";
//	if (anyUppercase(a1, 0))
//		cout << "True" << endl;
//	else cout << "False" << endl;
//
//	char a2[2] = "H";
//	if (anyUppercase(a2, 1))
//		cout << "True" << endl;
//	else cout << "False" << endl;
//
//	char a3[3] = "Hi";
//	if (anyUppercase(a3, 2))
//		cout << "True" << endl;
//	else cout << "False" << endl;
//
//	char a[6] = "Hello";
//	if (anyUppercase(a, 5))
//		cout << "True" << endl;
//	else cout << "False" << endl;
//
//	cout << countUppercase(a1, 0) << endl;
//	cout << countUppercase(a2, 1) << endl;
//	cout << countUppercase(a3, 2) << endl;
//	char b[6] = "HeLLo";
//	cout << countUppercase(b, 5) << endl;
//
//	cout << firstUppercase(a1, 0) << endl;
//	cout << firstUppercase(a2, 1) << endl;
//	cout << firstUppercase(a3, 2) << endl;
//	char c[6] = "hellO";
//	cout << firstUppercase(c, 5) << endl;
//	cout << firstUppercase(b, 5) << endl;
//	cout << firstUppercase(a, 5) << endl;
//
//	cout << indexOfLeast(a1, 0) << endl;
//	cout << indexOfLeast(a2, 1) << endl;
//	cout << indexOfLeast(a3, 2) << endl;
//	char d[6] = "bdace";
//	cout << indexOfLeast(d, 5) << endl;
//	char e[6] = "sldkk";
//	cout << indexOfLeast(e, 5) << endl;
//}