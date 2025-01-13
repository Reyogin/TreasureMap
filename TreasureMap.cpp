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

void TreasureMap::addMountain(int row, int col)
{
	if (!m_treasure.contains(std::make_pair(row, col)))
	{
		m_mountains.emplace(row, col);
	}
}

void TreasureMap::addTreasure(int row, int col, int nb)
{
	auto coordinates = std::make_pair(row, col);
	if (!m_mountains.contains(coordinates))
	{
		m_treasure.emplace(coordinates, nb);
	}
}

void TreasureMap::addAdventurer(Adventurer& adventurer)
{
	auto coordinates = std::make_pair(adventurer.getRow(), adventurer.getCol());

	if (!m_mountains.contains(coordinates))
	{
		m_adventurers.emplace(std::move(adventurer));
	}
}

static std::vector<std::string> processLine(std::string& str)
{
	std::vector<std::string> res;

	str.erase(std::remove(str.begin(), str.end(), ' '), str.end());

	std::size_t pos = 0;

	while ((pos = str.find('-')) != std::string::npos)
	{
		auto token = str.substr(0, pos);
		res.push_back(token);
		str = str.substr(pos + 1);
	}
	res.push_back(str);

	return res;
}

void TreasureMap::moveAdventurer(Adventurer& adventurer, std::string const& moves)
{

}

void TreasureMap::runSimulation()
{

}

std::string TreasureMap::getSimulationResult() const
{
	std::ostringstream oss;

	oss << std::format("C - {} - {}", m_height, m_width) << std::endl;

	for (auto const& mountain : m_mountains)
		oss << std::format("M - {} - {}", mountain.first, mountain.second) << std::endl;

	for (auto const& treasure : m_treasure)
		oss << std::format("T - {} - {} - {}", treasure.first.first, treasure.first.second, treasure.second) << std::endl;

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
			std::pair<int, int> current_coordinates{ i,j };
			if (auto adventurer = std::find_if(m_adventurers.begin(), m_adventurers.end(), [&](Adventurer const& adventurer) {
				return adventurer.getRow() == current_coordinates.first && adventurer.getCol() == current_coordinates.second;
				}); adventurer != m_adventurers.end())
				std::cout << std::format("A({}) ", adventurer->getName());
			else if (m_mountains.contains(current_coordinates))
				std::cout << "M ";
			else if (auto treasure = m_treasure.find(current_coordinates); treasure != m_treasure.end())
				std::cout << std::format("T({}) ", treasure->second);
			else
				std::cout << ". ";
		}
		std::cout << std::endl;
	}
}
