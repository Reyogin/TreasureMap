#pragma once

#include <string>

enum class Direction
{
	NORTH = 0,
	EAST = 1,
	SOUTH = 2,
	WEST = 3,
	INVALID = 4
};

static Direction fromChar(std::string str)
{
	if (str == "N")
		return Direction::NORTH;
	if (str == "E")
		return Direction::EAST;
	if (str == "S")
		return Direction::SOUTH;
	if (str == "W")
		return Direction::WEST;
	return Direction::INVALID;
}

static std::string toStr(Direction const& direction)
{
	switch (direction)
	{
	case Direction::NORTH:
		return "N";
	case Direction::EAST:
		return "E";
	case Direction::SOUTH:
		return "S";
	case Direction::WEST:
		return "W";
	default:
		return "INVALID";
	}
}

static std::pair<int, int> getMove(Direction direction)
{
	switch (direction)
	{
	case Direction::NORTH:
		return { 0,-1 };
	case Direction::EAST:
		return { 1,0 };
	case Direction::SOUTH:
		return { 0,1 };
	case Direction::WEST:
		return { -1,0 };
	default:
		return { 0,0 };
	}
}

