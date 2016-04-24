#ifndef HISTORY_INCLUDED
#define HISTORY_INCLUDED

#include "globals.h"

class History
{
	public:
		History(int nRows, int nCols);
	    bool record(int r, int c);
	    void display() const;
	private:
		int m_grid[MAXROWS][MAXCOLS];
		int m_rows;
		int m_cols;
		void setCellStatus(int r, int c, int status);
};

#endif // HISTORY_INCLUDED