#include "pch.h"
#include "Crossover.h"

SudokuBoard doRoulette(SudokuBoard solutionBoard)
{
	SudokuBoard candidates[ROULETTE_POP];
	int position[ROULETTE_POP] = { -1, -1, -1, -1, -1, -1, -1 };
	int count = 0;

	while (count != 7)
	{
		int random = intRand(0, pop_size - 1);
		bool exists = std::find(std::begin(position), std::end(position), random) != std::end(position);
		if (!exists)
		{
			position[count] = random;
			candidates[count] = sudokuPopGen[0][random];
			count++;
		}
	}

	int largest = 0;
	for (int i = 0; i < ROULETTE_POP; i++)
	{
		candidates[i].calculateFitness(solutionBoard);
		if (candidates[i].getFitness() > candidates[largest].getFitness())
		{
			largest = i;
		}
	}
	return candidates[largest];
}

void Crossover::performCrossover(SudokuBoard solutionBoard)
{
	num_elements = 0;
	while (num_elements < pop_size - 1)
	{
		int pos = num_elements;
		SudokuBoard parentA = doRoulette(solutionBoard);
		SudokuBoard parentB = doRoulette(solutionBoard);

		SudokuBoard childA = parentA;
		SudokuBoard childB = parentB;

		if (intRand(0, 100) <= CROSSOVER_CHANCE)
		{
			int num_iterations = intRand(1, 3);
			for (int i = 0; i < num_iterations; i++)
			{
				int length = intRand(3, 6);
				int column = intRand(0, 9 - length);
				int rowA = intRand(0, 8);
				int rowB = intRand(0, 8);

				for (int j = 0; j < length; j++)
				{
					auto cellA = childA.SudokuMap[rowA][column + j];
					auto cellB = childB.SudokuMap[rowB][column + j];

					childA.SudokuMap[rowA][column + j] = cellB;
					childB.SudokuMap[rowB][column + j] = cellA;

					arrayFill[rowA][column + j]++;
					arrayFill[rowB][column + j]++;
				}

				childA.calculateFitness(solutionBoard);
				childB.calculateFitness(solutionBoard);
			}
		}
		sudokuPopGen[1][pos] = (childA.getFitness() > childB.getFitness() ? childA : childB);
		num_elements++;
	}
}