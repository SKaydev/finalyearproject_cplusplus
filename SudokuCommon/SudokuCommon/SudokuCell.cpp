#include "pch.h"
#include "SudokuCell.h"

void SudokuCell::setPosition(coordinates position)
{
	this->position = position;
	generateOptimalNeighbours();
}

void SudokuCell::generateOptimalNeighbours() 
{
	for (int r = 0; r < 9; r++)
	{
		neighbours.insert({r, position.y});
	}

	for (int c = 0; c < 9; c++)
	{
		neighbours.insert({position.x, c});
	}

	auto floorx = (position.x / 3) * 3;
	auto floory = (position.y / 3) * 3;

	for (int i = floorx; i < position.x; ++i)
	{
		for (int j = floory; j < position.y; ++j)
		{
			neighbours.insert({ i, j });
		}
	}
}