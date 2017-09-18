#include <iostream>
#include "History.h"
using namespace std;

//initialize a Hisotry object
//create an empty grid ('.' means empty, without any record) with nRows and nCols 
//doesn't output the grid yet
History::History(int nRows, int nCols)
{
	m_rows = nRows;
	m_cols = nCols;
	for (int r = 0; r < m_rows; r++)
		for (int c = 0; c < m_cols; c++)
			m_grid[r][c] = '.';
}

//record the player's move
bool History::record(int r, int c)
{
	if (r >= 1 && r <= m_rows && c >= 1 && c <= m_cols)
	{
		if (m_grid[r-1][c-1] == '.')	//if it's player's first time landed on this grid point
			m_grid[r-1][c-1] = 'A';		//change '.' to 'A'
		else if (m_grid[r-1][c-1] == 'Z')	//if player has been to this grid point for over 26 times
			m_grid[r-1][c-1] = 'Z';		//keep it as Z
		else
			m_grid[r-1][c-1]++;		//otherwise, the character increment; A - Z means 1 to 26 times.
		return true;	//return true after recording the move
	}
	else 
		return false;	//if the player's position is out of bound, return false
}

//output the grid
void History::display() const
{
	clearScreen();
	for (int r = 0; r < m_rows; r++)
	{
		for (int c = 0; c < m_cols; c++)
			cout << m_grid[r][c];
		cout << endl;
	}
	cout << endl;
}