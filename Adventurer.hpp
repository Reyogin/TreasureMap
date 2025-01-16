#pragma once

#include "Direction.hpp"

#include <string>

class Adventurer
{
public:
	Adventurer(std::string name, int row, int col, Direction direction, std::string moves);

	void changeDirection(char c);

	std::string printAdventurer() const;

	std::string const& getName() const;
	int getRow() const;
	void setRow(int row);
	int getCol() const;
	void setCol(int col);
	Direction const& getDirection() const;
	int getTreasures() const;
	void addTreasure();
	std::string const& getMoves() const;

	friend auto operator<=>(Adventurer const&, Adventurer const&) = default;
private:
	std::string m_name;
	int m_row;
	int m_col;
	Direction m_direction;
	int m_gatheredTreasure = 0;
	std::string m_moves;
};