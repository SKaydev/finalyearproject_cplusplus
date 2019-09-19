#include "pch.h"
#include "Mutation.h"

void Mutation::performMutation(SudokuBoard board)
{
	for (int i = 0; i < pop_size; i++)
	{
		for(int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++) 
			{
				if (intRand(0, 100) <= MUTATION_CHANCE)
				{
					sudokuPopGen[1][i].SudokuMap[i][j] = intRand(1, 9);
				}
			}
		}
		sudokuPopGen[1][i].calculateFitness(board);
	}
}