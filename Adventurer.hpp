#pragma once

#include <string>

namespace
{
	enum class Direction
	{
		NORTH = 0,
		EAST = 1,
		SOUTH = 2,
		WEST = 3,
		INVALID = 4
	};

	Direction fromChar(char c)
	{
		switch (c)
		{
		case 'N':
			return Direction::NORTH;
		case 'E':
			return Direction::EAST;
		case 'S':
			return Direction::SOUTH;
		case 'W':
			return Direction::WEST;
		default:
			return Direction::INVALID;
		}
	}

	std::pair<int, int> getMove(Direction direction)
	{
		switch (direction)
		{
		case Direction::NORTH:
			return { -1,0 };
		case Direction::EAST:
			return { 0,1 };
		case Direction::SOUTH:
			return { 1,0 };
		case Direction::WEST:
			return { 0,-1 };
		default:
			return { 0,0 };
		}
	}
}

class Adventurer
{
public:
	Adventurer(std::string name, int row, int col, Direction direction);

	void changeDirection(char c);

	std::string printAdventurer() const;

	std::string const& getName() const;
	int getRow() const;
	int getCol() const;
	Direction const& getDirection() const;
	int getTreasures() const;

private:
	std::string m_name;
	int m_row;
	int m_col;
	Direction m_direction;
	int m_gatheredTreasure = 0;
};