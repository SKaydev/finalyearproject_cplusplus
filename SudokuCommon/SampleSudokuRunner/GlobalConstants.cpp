#include "pch.h"
#include "GlobalConstants.h"

SudokuBoard sudokuPopGen[2][pop_size] = {};
int currentGen = 0;
std::atomic<int> num_elements = 0;
int arrayFill[9][9] = {};