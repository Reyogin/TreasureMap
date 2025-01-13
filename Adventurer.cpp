#include "Adventurer.hpp"

#include <format>
#include <memory>

Adventurer::Adventurer(std::string name, int row, int col, Direction direction)
	: m_name(std::move(name)), m_row(row), m_col(col), m_direction(direction)
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
	return std::format("A - {} - {} - {} - {} - {}", m_name, m_row, m_col, m_direction, m_gatheredTreasure);
}

std::string const& Adventurer::getName() const
{
	return m_name;
}

int Adventurer::getRow() const
{
	return m_row;
}

int Adventurer::getCol() const
{
	return m_col;
}

Direction const& Adventurer::getDirection() const
{
	return m_direction;
}

int Adventurer::getTreasures() const
{
	return m_gatheredTreasure;
}