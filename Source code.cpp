#include<stdio.h>
#include<iostream>
using namespace std;

bool FindUnassignedLocation(int sudoku[N][N], int &row, int &col);
bool UsedInRow(int sudoku[N][N], int row, int num);
bool UsedInCol(int sudoku[N][N], int col, int num);
bool UsedInBox(int sudoku[N][N], int boxStartRow, int boxStartCol, int num);
bool isSafe(int sudoku[N][N], int row, int col, int num);
bool SolveSudoku(int sudoku[N][N]);
void initSudoku(int sudoku[N][N]);
void generateSudoku(int sudoku[N][N], int level);
bool isGenerated(int sudoku[N][N]);
bool checkSudoku(int grid[N][N]);


void initSudoku(int sudoku[N][N])
{
	for (int row = 0; row < N; row++)
	for (int col = 0; col < N; col++)
		sudoku[row][col] = UNASSIGNED;
	
}

// This function finds an entry in sudoku that is still unassigned

bool FindUnassignedLocation(int sudoku[N][N], int &row, int &col)
{
	for (row = 0; row < N; row++)
	for (col = 0; col < N; col++)
	if (sudoku[row][col] == UNASSIGNED)
		return true;
	return false;
}

/* Returns a boolean which indicates whether any assigned entry
in the specified row matches the given number. */
bool UsedInRow(int sudoku[N][N], int row, int num)
{
	for (int col = 0; col < N; col++)
	if (sudoku[row][col] == num)
		return true;
	return false;
}

/* Returns a boolean which indicates whether any assigned entry
in the specified column matches the given number. */
bool UsedInCol(int sudoku[N][N], int col, int num)
{
	for (int row = 0; row < N; row++)
	if (sudoku[row][col] == num)
		return true;
	return false;
}

/* Returns a boolean which indicates whether any assigned entry
within the specified 3x3 box matches the given number. */
bool UsedInBox(int sudoku[N][N], int boxStartRow, int boxStartCol, int num)
{
	for (int row = 0; row < 3; row++)
	for (int col = 0; col < 3; col++)
	if (sudoku[row + boxStartRow][col + boxStartCol] == num)
		return true;
	return false;
}

/* Returns a boolean which indicates whether it will be legal to assign
num to the given row,col location. */
bool isSafe(int sudoku[N][N], int row, int col, int num)
{
	/* Check if 'num' is not already placed in current row,
	current column and current 3x3 box */
	return !UsedInRow(sudoku, row, num) &&
		!UsedInCol(sudoku, col, num) &&
		!UsedInBox(sudoku, row - row % 3, col - col % 3, num);
}


bool SolveSudoku(int sudoku[N][N])
{
	int row, col;

	// If there is no unassigned location, we are done
	if (!FindUnassignedLocation(sudoku, row, col))
		return true; // success!

	// consider digits 1 to 9
	for (int num = 1; num <= 9; num++)
	{
		// if looks promising
		if (isSafe(sudoku, row, col, num))
		{
			// make tentative assignment
			sudoku[row][col] = num;

			// return, if success
			if (SolveSudoku(sudoku))
				return true;

			// failure, unmake & try again
			sudoku[row][col] = UNASSIGNED;
		}
	}
	return false;
}

bool isGenerated(int sudoku[N][N])
{
	for (int row = 0; row < N; row++)
	for (int col = 0; col < N; col++)
	{
		if (sudoku[row][col] == UNASSIGNED)
			return true;
	}
	return false;
}

void generateSudoku(int sudoku[N][N], int level)
{
	System::Random^ rnd = gcnew System::Random();

	initSudoku(sudoku);
	sudoku[0][0] = rnd->Next(1, 9);
	sudoku[4][4] = rnd->Next(1, 9);
	sudoku[8][8] = rnd->Next(1, 9);
	SolveSudoku(sudoku);

	for (int row = 0; row < N; row++)
	for (int col = 0; col < N; col++)
	{
		if (levelType == EASY)
		{
			if (rnd->Next(0,4) == 0)
				sudoku[row][col] = UNASSIGNED;
		}
		else if (levelType == MEDIUM)
		{
			if (rnd->Next(0, 3) == 0)
				sudoku[row][col] = UNASSIGNED;
		}

		else
		{
			if (rnd->Next(0, 2) == 0)
				sudoku[row][col] = UNASSIGNED;
		}
	}

	if (!isGenerated(sudoku))
		generateSudoku(sudoku,levelType);

	return;

}

bool checkSudoku(int grid[N][N])
{
	
	
	// check in col

	for (int i = 0; i < N; i++)
	for (int j = 0; j < N - 1;j++)
	for (int k = j + 1; k < N;k++)
	if (grid[i][j] == grid[i][k])
		return false;

	// check in rwo

	for (int _i = 0; _i < N; _i++)
	for (int _j = 0; _j < N - 1; _j++)
	for (int _k = _j + 1; _k < N; _k++)
	if (grid[_j][_i] == grid[_k][_i])
		return false;

	return true;

}
