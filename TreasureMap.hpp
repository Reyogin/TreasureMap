#pragma once

#include "Adventurer.hpp"

#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>

class TreasureMap
{
public:
	TreasureMap() = default;

	void setMapWidth(int width);
	void setMapHeight(int height);

	void addTreasure(int row, int col, int nb);
	void addMountain(int row, int col);
	void addAdventurer(Adventurer& adventurer);

	void moveAdventurer(Adventurer&, std::string const& moves);
	std::string getSimulationResult() const;

	//For debug purposes
	void printMap();
private:
	int m_width = 0;
	int m_height = 0;
	std::map<std::pair<int, int>, int> m_treasure;
	std::set<Adventurer> m_adventurers;
	std::set<std::pair<int, int>> m_mountains;
};