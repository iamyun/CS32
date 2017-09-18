#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
	stack<Coord> coordStack;

	if (sr == er && sc == ec)
		return true;

	coordStack.push(Coord(sr, sc)); //push starting coordinate to the stack 
	maze[sr][sc] = '#';		//set maze[sr][sc] to have a value other than '.'

	while (!coordStack.empty())
	{
		Coord cur = coordStack.top();	//record the coordinate before poppoing it off the stack
		int row = cur.r();
		int col = cur.c();
		coordStack.pop();	
		cout << row << "," << col << endl;
		if (row == er && col == ec) //check if the current coordinate is equal to the ending coordinate
			return true;
		//check North
		if (maze[row-1][col] == '.')
		{
			coordStack.push(Coord(row-1, col));
			maze[row-1][col] = '#';
		}
		//check East
		if (maze[row][col+1] == '.')
		{
			coordStack.push(Coord(row, col+1));
			maze[row][col+1] = '#';
		}
		//check South
		if (maze[row+1][col] == '.')
		{
			coordStack.push(Coord(row+1, col));
			maze[row+1][col] = '#';
		}
		//check West
		if (maze[row][col-1] == '.')
		{
			coordStack.push(Coord(row, col-1));
			maze[row][col-1] = '#';
		}
	}

	return false;
}

int main()
{
	string maze[10] = {
		"XXXXXXXXXX",
		"X.......@X",
		"XX@X@@.XXX",
		"X..X.X...X",
		"X..X...@.X",
		"X....XXX.X",
		"X@X....XXX",
		"X..XX.XX.X",
		"X...X....X",
		"XXXXXXXXXX"
	};

	if (pathExists(maze, 10, 10, 6, 4, 1, 1))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;
}