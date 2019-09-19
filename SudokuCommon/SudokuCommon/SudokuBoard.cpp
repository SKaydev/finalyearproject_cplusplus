#include "pch.h"
#include "SudokuBoard.h"
#include "InvalidSudokuException.h"

namespace Sudoku
{
	std::random_device rd;
	std::mt19937 randomGen(rd());

	SudokuBoard SudokuBoard::generateNewBoard()
	{
		SudokuBoard board{};
		stringstream output;

		for (auto i = 0; i < 10; ++i) {
			if (board.fillCells(0))
			{
				const char * error = "Unable to generate board";
				const char * file = "SudokuBoard.cpp";
				const char * func = "SudokuBoard::generateNewBoard()";
				throw InvalidSudokuException(error, file, 18, func);
			}
			board.printBoard();
			return board;
		}
	}

	void SudokuBoard::reset()
	{
		for (auto cell : cells)
		{
			cell->value = 0;
		}
	}

	bool SudokuBoard::fillCells(int index)
	{
		// get first cell and tail
		auto cell = cells.at(index);

		set<int> neighborValues = {};

		for (auto &neighbor : cell->neighbours) {
			auto value = this->at(neighbor)->value;
			neighborValues.insert(value);
		}

		vector<int> options;
		set_difference(
			VALID_VALUES.begin(), VALID_VALUES.end(),
			neighborValues.begin(), neighborValues.end(),
			inserter(options, options.begin())
		);
		shuffle(options.begin(), options.end(), randomGen);

		for (auto option : options) {
			cell->value = option;

			if (index == cells.size() - 1 || fillCells(index + 1)) {
				return true;
			}
		}

		// out of options backtrack
		cell->value = 0;
		return false;
	}

	void SudokuBoard::printBoard() {
		cout << '\n' << "----------------------------------" << '\n';

		for (int i = 0; i < SIZE; i++) {
			cout << "| ";

			for (int j = 0; j < SIZE; j++) {
				auto index = resolvePosition({ i, j }); // YOOOO structs
				auto cell = cells[index];
				auto value = cell->value;

				if (cell->value > 0) {
					cout << cell->value << "  ";
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

	coordinates SudokuBoard::parseCoordinate(int index)
	{
		return coordinates{
			index / SIZE,
			index % SIZE
		};
	}

	int SudokuBoard::resolvePosition(const coordinates &position)
	{
		return position.x * SIZE + position.y;
	}
};