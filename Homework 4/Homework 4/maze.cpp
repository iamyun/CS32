#include <iostream>
using namespace std;

class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {};
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
	//if the start location is the ending location, immediately return true
	if (sr == er && sc == ec)
		return true;
	maze[sr][sc] = '#';	//mark that we have visited the location

	//check the four directions
	Coord dir[4] = { Coord(sr, sc - 1), Coord(sr + 1, sc), Coord(sr, sc + 1), Coord(sr - 1, sc) };
	//for each of the directions, if the location is unvisited, call pathExist
	//if that returns true, then return true
	for (int i = 0; i < 4; i++)
	{
		if (maze[dir[i].r()][dir[i].c()] == '.')
		{
			bool check = pathExists(maze, nRows, nCols, dir[i].r(), dir[i].c(), er, ec);
			if (check)
				return true;
		}
	}
	return false;	//if checked all possible paths but never returned true, return false.
}

//int main()
//{
//	string maze[10] = {
//		"XXXXXXXXXX",
//		"X.......@X",
//		"XX@X@@.XXX",
//		"X..X.X...X",
//		"X..X...@.X",
//		"X....XXX.X",
//		"X@X....XXX",
//		"X..XX.XX.X",
//		"X...X....X",
//		"XXXXXXXXXX"
//	};
//
//
//	if (pathExists(maze, 10, 10, 6, 4, 6, 4))
//		cout << "Solvable!" << endl;
//	else
//		cout << "Out of luck!" << endl;
//
//	string maze1[10] = {
//		"XXXXXXXXXX",
//		"X.......@X",
//		"XX@X@@.XXX",
//		"X..X.X...X",
//		"X..X...@.X",
//		"X....XXX.X",
//		"X@X....XXX",
//		"X..XX.XX.X",
//		"X...X....X",
//		"XXXXXXXXXX"
//	};
//
//	if (pathExists(maze1, 10, 10, 6, 4, 6, 5))
//		cout << "Solvable!" << endl;
//	else
//		cout << "Out of luck!" << endl;
//
//	string maze2[10] = {
//		"XXXXXXXXXX",
//		"X.......@X",
//		"XX@X@@.XXX",
//		"X..X.X...X",
//		"X..X...@.X",
//		"X....XXX.X",
//		"X@X....XXX",
//		"X..XX.XX.X",
//		"X...X....X",
//		"XXXXXXXXXX"
//	};
//
//	if (pathExists(maze2, 10, 10, 6, 4, 6, 2))
//		cout << "Solvable!" << endl;
//	else
//		cout << "Out of luck!" << endl;
//
//	string maze3[10] = {
//		"XXXXXXXXXX",
//		"X.......@X",
//		"XX@X@@.XXX",
//		"X..X.X...X",
//		"X..X...@.X",
//		"X....XXX.X",
//		"X@X....XXX",
//		"X..XX.XX.X",
//		"X...X....X",
//		"XXXXXXXXXX"
//	};
//
//	if (pathExists(maze3, 10, 10, 6, 4, 1, 1))
//		cout << "Solvable!" << endl;
//	else
//		cout << "Out of luck!" << endl;
//
//}