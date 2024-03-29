#include "pch.h"
#include "SudokuBoard.h"
#include "GlobalConstants.h"
#include "Operators/Crossover.h"
#include "Mutation.h"
#include <iostream>
#include <random>
#include <regex>
#include <chrono>
#include <thread>
#include <fstream>

Crossover crossover;
Mutation mutation;

void bubbleSort(int a, int n)
{
	if (n == 1)
		return;

	for (int j = 0; j < n - 1; j++)
	{
		if (sudokuPopGen[a][j].getFitness() > sudokuPopGen[a][j + 1].getFitness())
		{
			std::swap(sudokuPopGen[a][j].SudokuMap, sudokuPopGen[a][j + 1].SudokuMap);
			std::swap(sudokuPopGen[a][j].fitness, sudokuPopGen[a][j + 1].fitness);
		}
	}

	bubbleSort(a, n - 1);
}

void weighFitness(SudokuBoard solutionBoard)
{
	for (int i = 0; i < pop_size; i++)
	{
		sudokuPopGen[0][i].calculateFitness(solutionBoard);
		sudokuPopGen[1][i].calculateFitness(solutionBoard);
	}
}

int getAverageFitness()
{
	int averageFitness = 0;

	for (int i = 0; i < pop_size; i++)
	{
		averageFitness = averageFitness + sudokuPopGen[0][i].getFitness();
	}

	return averageFitness / pop_size;
}

int getTotalFitness()
{
	int totalFitness = 0;

	for (int i = 0; i < pop_size; i++)
	{
		totalFitness += sudokuPopGen[0][i].getFitness();
	}

	return totalFitness;
}

void populateRandomly()
{
	for (int i = 0; i < pop_size; i++)
	{
		sudokuPopGen[0][i] = *SudokuBoard(true); // explicity marked at 0, as it's designed to only run at the start of runtime.
	}
}

int isFitnessGreaterThanAnyElement(SudokuBoard board, int arr[3])
{
	for (int i = 0; i < sizeof(arr) / sizeof(*arr); i++)
	{
		auto fitness = board.getFitness();
		if (fitness > arr[i])
		{
			return i;
		}
	}
	return -1;
}

int isFitnessSmallerThanAnyElement(SudokuBoard board, int arr[3])
{
	for (int i = 0; i < sizeof(arr) / sizeof(*arr); i++)
	{
		auto fitness = board.getFitness();
		if (fitness <= arr[i])
		{
			return i;
		}
	}
	return -1;
}

void performSelectiveElitism()
{
	bubbleSort(0, pop_size);
	bubbleSort(1, pop_size);

	int temp = pop_size - 1;
	for (int i = 0; i < BOARDS_TO_BRING_FORWARD; i++)
	{
		sudokuPopGen[1][i] = sudokuPopGen[0][temp - i];
	}

	bubbleSort(0, pop_size);
	bubbleSort(1, pop_size);
}

int main()
{
	// set the seed
	std::srand((unsigned)time(NULL));

	std::ofstream outputfile;
	outputfile.open("output.txt", std::ios::app);

	memset(arrayFill, 0, sizeof(arrayFill));
	SudokuBoard solutionBoard = solutionBoard.generateNewBoard();

	std::cout << "Generated the board listed below:" << std::endl;
	solutionBoard.printBoard();

	std::cout << "Will begin solving using the following parameters:" << std::endl
	<< "Population Size: " << pop_size << std::endl
	<< "Number of generations: " << gen_size << std::endl;

	populateRandomly();

	while (currentGen <= gen_size)
	{
		std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

		weighFitness(solutionBoard);
		crossover.performCrossover(solutionBoard);
		mutation.performMutation(solutionBoard);
		weighFitness(solutionBoard);
		performSelectiveElitism();
		
		std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

		auto duration = std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count();

		outputfile << "Current Generation: " << currentGen + 1 << endl
			<< "Current average fitness: " << getAverageFitness() << endl
			<< "Current total fitness: " << getTotalFitness() << endl
			<< "Duration of workload: " << duration << "s" << endl;

		outputfile << "DEBUG STATS: " << endl << "{ ";

		for (int i = 0; i < pop_size; i++)
		{
			outputfile << sudokuPopGen[1][i].getFitness() << ", ";
		}

		outputfile << "}" << endl;

		cout << "Current Generation: " << currentGen + 1 << endl
			<< "Current average fitness: " << getAverageFitness() << endl
			<< "Current total fitness: " << getTotalFitness() << endl
			<< "Duration of workload: " << duration << "s" << endl;
		
		for (int i = 0; i < pop_size; i++)
		{
			SudokuBoard board = sudokuPopGen[1][i];
			sudokuPopGen[0][i] = board;
		}

		currentGen++;
	}
	return 0;
}