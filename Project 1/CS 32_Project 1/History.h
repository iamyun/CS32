#ifndef HISTORY

#define HISTORY

#include "globals.h"

class History
{
public: 
	//Constructor
	History(int nRows, int nCols);

	//Mutators
	bool record(int r, int c);
	void display() const;

private:
	int m_rows;
	int m_cols;
	char m_grid[MAXROWS][MAXCOLS];
};

#endif // !HISTORY
