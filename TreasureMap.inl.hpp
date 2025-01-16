#pragma once

#include "TreasureMap.hpp"

namespace {

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

}

template<typename IStream>
void execSimulation(IStream stream, TreasureMap& treasureMap)
{
	std::string str;
	while (std::getline(stream, str))
	{
		auto processedLine = processLine(str);
		auto action = processedLine[0];

		if (action.length() > 1 && action.at(0) == '#')
			continue;
		if (action == "C")
		{
			treasureMap.setMapWidth(std::stoi(processedLine[1]));
			treasureMap.setMapHeight(std::stoi(processedLine[2]));
		}
		else if (action == "M")
			treasureMap.addMountain(std::stoi(processedLine[1]), std::stoi(processedLine[2]));
		else if (action == "T")
			treasureMap.addTreasure(std::stoi(processedLine[1]), std::stoi(processedLine[2]), std::stoi(processedLine[3]));
		else if (action == "A")
		{
			auto coordinates_col = std::stoi(processedLine[2]);
			auto coordinates_row = std::stoi(processedLine[3]);
			if (treasureMap.isValid(coordinates_row, coordinates_col))
			{
				Adventurer adventurer(processedLine[1], coordinates_col, coordinates_row, fromChar(processedLine[4]), processedLine[5]);
				treasureMap.addAdventurer(adventurer);
			}
		}
		else
		{
			std::cerr << "Invalid input" << std::endl;
			return;
		}
	}
	for (auto& [adventurerName, adventurer] : treasureMap.getAdventurers())
		treasureMap.moveAdventurer(adventurer, adventurer.getMoves());
}