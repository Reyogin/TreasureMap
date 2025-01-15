#include "TreasureMap.hpp"

#include <algorithm>
#include <format>
#include <sstream>
#include <string>
#include <vector>

void TreasureMap::setMapWidth(int width)
{
	m_width = width;
}

void TreasureMap::setMapHeight(int height)
{
	m_height = height;
}

void TreasureMap::addMountain(int col, int row)
{
	if (!m_treasure.contains(std::make_pair(col, row)))
	{
		m_mountains.emplace(col, row);
	}
}

void TreasureMap::addTreasure(int col, int row, int nb)
{
	auto coordinates = std::make_pair(col, row);
	if (!m_mountains.contains(coordinates))
	{
		m_treasure.emplace(coordinates, nb);
	}
}

void TreasureMap::addAdventurer(Adventurer& adventurer)
{
	auto coordinates = std::make_pair(adventurer.getCol(), adventurer.getRow());

	if (!m_mountains.contains(coordinates))
	{
		m_adventurers.emplace(std::move(adventurer));
	}
}

bool TreasureMap::isValid(int row, int col) const
{
	if (row < 0 || row >= this->m_height || col < 0 || col >= this->m_width)
		return false;
	//current coordinates aren't a mountain
	return m_mountains.find({ col, row }) == m_mountains.end();
}

void TreasureMap::moveAdventurer(Adventurer& adventurer, std::string const& moves)
{
	for (auto const& c : moves)
	{
		switch (c)
		{
		case 'A':
		{
			auto moveTowards = getMove(adventurer.getDirection());
			//The next cell is valid
			auto rowMove = adventurer.getRow() + moveTowards.second;
			auto colMove = adventurer.getCol() + moveTowards.first;
			if (isValid(rowMove, colMove))
			{
				adventurer.setRow(rowMove);
				adventurer.setCol(colMove);
				if (auto treasureIt = m_treasure.find({ colMove, rowMove }); treasureIt != m_treasure.end() && treasureIt->second > 0)
				{
					treasureIt->second--;
					adventurer.addTreasure();
				}
			}
			break;
		}
		case 'D':
		case 'G':
			adventurer.changeDirection(c);
			break;
		default:
			break;
		}
	}
}

void TreasureMap::runSimulation(std::string const& filename)
{
	std::ifstream file(filename);

	if (!file.is_open())
	{
		//not a file, assuming we're reading a string
		std::istringstream stringStream(filename);
		execSimulation<std::istringstream>(std::move(stringStream), *this);
	}
	else
	{
		//reading from file
		execSimulation<std::ifstream>(std::move(file), *this);
		file.close();
	}
}

std::string TreasureMap::getSimulationResult() const
{
	std::ostringstream oss;

	oss << std::format("C - {} - {}", m_width, m_height) << std::endl;

	for (auto const& mountain : m_mountains)
		oss << std::format("M - {} - {}", mountain.first, mountain.second) << std::endl;

	for (auto const& treasure : m_treasure)
	{
		if (treasure.second > 0)
			oss << std::format("T - {} - {} - {}", treasure.first.first, treasure.first.second, treasure.second) << std::endl;
	}

	for (auto const& adventurer : m_adventurers)
		oss << adventurer.printAdventurer() << std::endl;

	return oss.str();
}

void TreasureMap::printMap()
{
	for (int i = 0; i < m_height; i++)
	{
		for (int j = 0; j < m_width; j++)
		{
			std::pair<int, int> current_coordinates{ j,i };
			if (auto adventurer = std::find_if(m_adventurers.begin(), m_adventurers.end(), [&](Adventurer const& adventurer) {
				return adventurer.getRow() == current_coordinates.first && adventurer.getCol() == current_coordinates.second;
				}); adventurer != m_adventurers.end())
				std::cout << std::format("A({}) ", adventurer->getName());
			else if (m_mountains.contains(current_coordinates))
				std::cout << "M ";
			else if (auto treasure = m_treasure.find(current_coordinates); treasure != m_treasure.end())
			{
				if (treasure->second > 0)
					std::cout << std::format("T({}) ", treasure->second);
				else
					std::cout << ". ";
			}
			else
				std::cout << ". ";
		}
		std::cout << std::endl;
	}
}

