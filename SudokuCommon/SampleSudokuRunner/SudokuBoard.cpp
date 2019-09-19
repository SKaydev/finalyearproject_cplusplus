#include "pch.h"
#include "SudokuBoard.h"
#include "InvalidSudokuException.h"

std::random_device rd;
std::mt19937 randomGen(rd());

int SudokuBoard::randElement(const int &min, const int &max) {
	static thread_local std::mt19937 generator;
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

SudokuBoard::SudokuBoard()
{
	SudokuBoard(false);
}


SudokuBoard::SudokuBoard(bool doRandom)
{
	if (doRandom)
	{
		for (int j = 0; j < 9; j++)
		{
			for (int k = 0; k < 9; k++)
			{
				SudokuMap[j][k] = randElement(1, 9);
			}
		}
	}
}

SudokuBoard SudokuBoard::generateNewBoard()
{
	SudokuBoard board{};
	board.fillCells();
	return board;
}

/** Reset the board to 0 values for all cells.
 */
void SudokuBoard::reset()
{
	SudokuMap[SIZE][SIZE] = { 0 };
}

/** Fills the cells for a valid new board
 */
void SudokuBoard::fillCells()
{
	//Fill the diagonal matrices
	fillDiagonal();

	//Fill in the empty cells
	fillEmpty(0, THIRD);
}

bool SudokuBoard::uniqueInAllScenarios(int row, int column, int num)
{
	return (uniqueInRow(row, num) &&
		uniqueInColumn(column, num) &&
		uniqueInSubSquare(row - (row % THIRD), column - (column % THIRD), num));
}

bool SudokuBoard::uniqueInSubSquare(int row, int column, int num)
{
	for (int i = 0; i < THIRD; i++)
		for (int j = 0; j < THIRD; j++)
			if (SudokuMap[row + i][column + j] == num)
				return false;

	return true;
}

bool SudokuBoard::uniqueInRow(int i, int num)
{
	for (int j = 0; j < SIZE; j++)
		if (SudokuMap[i][j] == num)
			return false;

	return true;
}

bool SudokuBoard::uniqueInColumn(int i, int num)
{
	for (int j = 0; j < SIZE; j++)
		if (SudokuMap[j][i] == num)
			return false;

	return true;
}

void SudokuBoard::fillDiagonal()
{
	for (int i = 0; i < SIZE; i += THIRD)
		fillSubSquare(i, i);
}

void SudokuBoard::fillSubSquare(int row, int column)
{
	int randNum;
	for (int i = 0; i < THIRD; i++)
	{
		for (int j = 0; j < THIRD; j++)
		{
			do
			{
				randNum = randElement(1, 9);
			} 
			while (!uniqueInSubSquare(row, column, randNum));

			SudokuMap[row + i][column + j] = randNum;
		}
	}
}

bool SudokuBoard::fillEmpty(int i, int j)
{
	if (j >= SIZE && i < SIZE - 1)
	{
		i = i + 1;
		j = 0;
	}
	if (i >= SIZE && j >= SIZE)
		return true;

	if (i < THIRD)
	{
		if (j < THIRD)
			j = THIRD;
	}
	else if (i < SIZE - THIRD)
	{
		if (j == (int)(i / THIRD)*THIRD)
			j = j + THIRD;
	}
	else
	{
		if (j == SIZE - THIRD)
		{
			i = i + 1;
			j = 0;
			if (i >= SIZE)
				return true;
		}
	}

	for (int num = 1; num <= SIZE; num++)
	{
		if (uniqueInAllScenarios(i, j, num))
		{
			SudokuMap[i][j] = num;
			if (fillEmpty(i, j + 1))
				return true;

			SudokuMap[i][j] = 0;
		}
	}
	return false;
}

/** Prints the board to std::cout
 */
void SudokuBoard::printBoard() {
	cout << '\n' << "----------------------------------" << '\n';

	for (int i = 0; i < SIZE; i++) {
		cout << "| ";

		for (int j = 0; j < SIZE; j++) {
			if (SudokuMap[i][j] > 0) {
				cout << SudokuMap[i][j] << "  ";
			}
			else {
				cout << "   ";
			}

			if (j % THIRD == THIRD - 1) {
				cout << "| ";
			}
		}
		if (i % THIRD == THIRD - 1) {
			cout << '\n' << "----------------------------------";
		}
		cout << '\n';
	}
}

void SudokuBoard::setFitness(int currentFitness)
{
	fitness = currentFitness;
}

int SudokuBoard::getFitness()
{
	return fitness;
}

void SudokuBoard::calculateFitness(SudokuBoard board) // This fitness function is not fit for purpose. Rewrite.
{
	// The fitness function should be 
	// 9x9 + 9x9 + 9x9

	int fitnessA = 0;
	int fitnessB = 0;
	int fitnessC = 0;
	
	//Correct elements on a row
	for (int a = 0; a < SIZE; a++)
	{
		for (int i = 0; i < SIZE; i++)
		{
			if (SudokuMap[a][i] == board.SudokuMap[a][i])
				fitnessA++;
		}
	}

	//Correct elements on a column
	for (int b = 0; b < SIZE; b++)
	{
		for (int i = 0; i < SIZE; i++)
		{
			if (SudokuMap[i][b] == board.SudokuMap[i][b])
				fitnessB++;
		}
	}
	
	//Correct subsquares, and their elements
	for (int i = 0; i < SIZE; i += THIRD)
		for (int j = 0; j < SIZE; j += THIRD)
			fitnessC += countValidSubSquareValues(i, j, board);

	setFitness(fitnessA + fitnessB + fitnessC);
}

int SudokuBoard::countValidSubSquareValues(int row, int column, SudokuBoard board)
{
	int num = 0;
	for (int i = 0; i < THIRD; i++)
	{
		for (int j = 0; j < THIRD; j++)
		{
			if (SudokuMap[row + i][column + j] == board.SudokuMap[row + i][column + j])
			{
				num++;
			}
		}
	}
	return num;
}