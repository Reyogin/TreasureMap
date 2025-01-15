#include "pch.h"

#include "TreasureMap.hpp"
#include <string>

TEST(TreasureMap, GivenTest) {
	TreasureMap treasureMap;
	std::string input = "C - 3 - 4\n"
					    "M - 1 - 0\n"
					    "M - 2 - 1\n"
					    "T - 0 - 3 - 2\n"
					    "T - 1 - 3 - 3\n"
					    "A - Lara - 1 - 1 - S - AADADAGGA\n";
	treasureMap.runSimulation(input);
	treasureMap.printMap();

	std::string output = "C - 3 - 4\n"
						 "M - 1 - 0\n"
						 "M - 2 - 1\n"
						 "T - 1 - 3 - 2\n"
						 "A - Lara - 0 - 3 - S - 3\n";

	EXPECT_EQ(output, treasureMap.getSimulationResult());
}