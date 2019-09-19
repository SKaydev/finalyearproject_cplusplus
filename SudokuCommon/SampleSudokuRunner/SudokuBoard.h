#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <deque>
#include <sstream>
#include <iterator>
#include <thread>
#include <random>

using namespace std;

class SudokuBoard
{
public:

	const int SIZE = 9;
	const int THIRD = 3;
	int fitness = 0;
	int SudokuMap[9][9] = { 0 };

	int randElement(const int & min, const int & max);
	
	SudokuBoard();
	SudokuBoard(bool doRandom);
	SudokuBoard generateNewBoard();

	void reset();
	void printBoard();
	void setFitness(int currentFitness);
	int getFitness();
	void calculateFitness(SudokuBoard board);

	inline SudokuBoard& operator = (SudokuBoard& other)
	{
		std::swap(SudokuMap, other.SudokuMap);
		std::swap(fitness, other.fitness);
		return *this;
	}

private:
	
	int countValidSubSquareValues(int row, int column, SudokuBoard board);
	void fillCells();
	bool uniqueInAllScenarios(int row, int column, int num);
	bool uniqueInSubSquare(int row, int column, int num);
	bool uniqueInRow(int i, int num);
	bool uniqueInColumn(int i, int num);
	void fillDiagonal();
	void fillSubSquare(int row, int column);
	bool fillEmpty(int i, int j);
};