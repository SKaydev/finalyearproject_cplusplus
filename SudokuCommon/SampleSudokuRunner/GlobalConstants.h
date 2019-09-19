#pragma once
#include <random>
#include <string>
#include <atomic>
#include "SudokuBoard.h"

// --------------------------------------------------------
// Global Constants
// --------------------------------------------------------
const int pop_size = 1000;
const int gen_size = 100;

const int ROULETTE_POP = 7;

const int CROSSOVER_CHANCE = 80;
const int MUTATION_CHANCE = 5;
const int BOARDS_TO_BRING_FORWARD = int((pop_size/100) * 5);
const int NUM_THREADS = 4;

extern std::random_device ran;
extern std::mt19937 randomG;
// --------------------------------------------------------

// --------------------------------------------------------
// Volatile Global Constants
// --------------------------------------------------------
extern int arrayFill[9][9];
extern int currentGen;
extern std::atomic<int> num_elements;
extern SudokuBoard sudokuPopGen[2][pop_size];
// --------------------------------------------------------

inline int intRand(const int &min, const int &max) {
	static thread_local std::mt19937 generator;
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}