#pragma once
#include <set>


struct coordinates
{
	int x = 0;
	int y = 0;
};

inline bool operator == (const coordinates &lhs, const coordinates &rhs) {
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

inline bool operator < (const coordinates &lhs, const coordinates &rhs) {
	return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y);
}

class SudokuCell
{
public:
	SudokuCell() {}

	coordinates position;
	std::set<coordinates> neighbours{};
	int value = 0;
	void setPosition(coordinates position);

private:
	void generateOptimalNeighbours();
};