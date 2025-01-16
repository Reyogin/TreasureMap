#include "Adventurer.hpp"

#include <format>
#include <memory>

Adventurer::Adventurer(std::string name, int col, int row, Direction direction, std::string moves)
	: m_name(std::move(name)), m_row(row), m_col(col), m_direction(direction), m_moves(std::move(moves))
{}

void Adventurer::changeDirection(char c)
{
	switch (c)
	{
	case 'D':
		m_direction = static_cast<Direction>((static_cast<int>(m_direction) + 1) % 4);
		break;
	case 'G':
		m_direction = static_cast<Direction>((static_cast<int>(m_direction) + 3) % 4);
		break;
	default:
		return;
	}
}

std::string Adventurer::printAdventurer() const
{
	return std::format("A - {} - {} - {} - {} - {}", getName(), getCol(), getRow(), toStr(getDirection()), getTreasures());
}

std::string const& Adventurer::getName() const
{
	return m_name;
}

int Adventurer::getRow() const
{
	return m_row;
}

void Adventurer::setRow(int row)
{
	m_row = row;
}

int Adventurer::getCol() const
{
	return m_col;
}

void Adventurer::setCol(int col)
{
	m_col = col;
}

Direction const& Adventurer::getDirection() const
{
	return m_direction;
}

int Adventurer::getTreasures() const
{
	return m_gatheredTreasure;
}

void Adventurer::addTreasure()
{
	m_gatheredTreasure++;
}

std::string const& Adventurer::getMoves() const
{
	return m_moves;
}
