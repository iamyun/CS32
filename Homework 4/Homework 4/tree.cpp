#include <iostream>
using namespace std;

int countIncludes(const char a1[], int n1, const char a2[], int n2)
{
	//if n1 < n2, there's no way that a2 is included in a1
	if (n1 < n2)
		return 0;

	//if n2 ==0, then there's an empty set in a2, which should always exist in a1, so return 1
	if (n2 == 0)
		return 1;

	int count = 0;

	//count how many ways a2 is included in a1 without the first element in a1
	//if a1[0] != a2[0], this will be the final count of ways a2 appears in a1
	count = countIncludes(a1 + 1, n1 - 1, a2, n2);

	//if a1[0] == a2[0], in this case, we will also need to count how many times a2
	//appears in a1 when the match of a2[0] is already picked to be in a1[0].
	//This count can be done be counting times a2 without a2[0] appears
	//in a1 without a1[0].
	//Since counting ways a2 appears in a1 with a1's first element is disjoint with ways a2 appears in 
	//a1 without a1's first element, adding those two cases gives the total count of ways a2
	//appears in a1 when a1[0] == a2[0]
	if (a1[0] == a2[0])
		count += countIncludes(a1 + 1, n1 - 1, a2 + 1, n2 - 1);

	return count;

}
//
//int main()
//{
//	char a1[8] = "skcekcb";
//	char a2[4] = "sec";
//	char b2[4] = "scb";
//	char c2[4] = "esc";
//	char d2[4] = "kcb";
//	cout << countIncludes(a1, 7, a2, 3);
//	cout << countIncludes(a1, 7, b2, 3);
//	cout << countIncludes(a1, 7, c2, 3);
//	cout << countIncludes(a1, 7, d2, 3);
//}