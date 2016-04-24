#include "History.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols)
	: m_rows(nRows), m_cols(nCols)
{
	 for (int r = 1; r <= m_rows; r++)
        for (int c = 1; c <= m_cols; c++)
            setCellStatus(r, c, EMPTY);
}

bool History::record(int r, int c)
{
	if (r >= 1  &&  r <= m_rows  &&  c >= 1  &&  c <= m_cols)
	{
		m_grid[r-1][c-1] += 1; 
		return true;
	}
	else
		return false;
}

void History::display() const
{
	char displayGrid[MAXROWS][MAXCOLS];
    int r, c;
	int nDead;
	
	for (r = 1; r <= m_rows; r++)
		for (c = 1; c <= m_cols; c++)
		{
			nDead = m_grid[r-1][c-1];
			if (nDead == EMPTY)
				displayGrid[r-1][c-1] = '.';
			else if (nDead >= 1 && nDead < 26)
			{
				displayGrid[r-1][c-1] = static_cast<char>('A' + (nDead-1));
			}
			else 
				displayGrid[r-1][c-1] = 'Z';
		}

	clearScreen();
	for (r = 1; r <= m_rows; r++)
    {
        for (c = 1; c <= m_cols; c++)
            cout << displayGrid[r-1][c-1];
        cout << endl;
    }
    cout << endl;
}

void History::setCellStatus(int r, int c, int status)
{
	m_grid[r-1][c-1] = status;
}