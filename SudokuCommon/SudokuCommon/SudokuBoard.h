#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <deque>
#include <sstream>
#include <iterator>
#include <thread>
#include <random>

#include "SudokuCell.h"

#ifdef SUDOKULIBRARY_EXPORTS  
#define SUDOKULIBRARY_API __declspec(dllexport)   
#else  
#define SUDOKULIBRARY_API __declspec(dllimport)   
#endif  

using namespace std;

using cellQueue = deque<shared_ptr<SudokuCell>>;

namespace Sudoku
{
	class SudokuBoard
	{
	public:
		
		static SUDOKULIBRARY_API SudokuBoard generateNewBoard();

		cellQueue cells;

		const int SIZE = 9;
		const int THIRD = 3;

		const set<int> VALID_VALUES = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		SudokuBoard() {
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					auto cell = make_shared<SudokuCell>(SudokuCell());
					cell->setPosition({ i, j });
					cells.push_back(cell);
				}
			}
		}

		void reset();

		bool fillCells(int index);

		void printBoard();

		coordinates parseCoordinate(int index);

		int resolvePosition(const coordinates &position);

		shared_ptr<SudokuCell> at(int index) {
			return this->cells.at(index);
		}

		shared_ptr<SudokuCell> at(coordinates position) {
			auto index = this->resolvePosition(position);
			return this->at(index);
		}
	};
}