#include "pch.h"

#include "TreasureMap.hpp"

#include <fstream>
#include <iostream>
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

	std::string output = "C - 3 - 4\n"
						 "M - 1 - 0\n"
						 "M - 2 - 1\n"
						 "T - 1 - 3 - 2\n"
						 "A - Lara - 0 - 3 - S - 3\n";

	EXPECT_EQ(output, treasureMap.getSimulationResult());
}

TEST(TreasureMap, SpinOnTreasure) {
	TreasureMap treasureMap;
	std::string input = "C - 3 - 4\n"
		"M - 1 - 0\n"
		"M - 2 - 1\n"
		"T - 0 - 3 - 2\n"
		"T - 1 - 3 - 3\n"
		"A - Lara - 0 - 3 - S - GGGGGGGG\n";
	treasureMap.runSimulation(input);

	std::string output = "C - 3 - 4\n"
		"M - 1 - 0\n"
		"M - 2 - 1\n"
		"T - 0 - 3 - 2\n"
		"T - 1 - 3 - 3\n"
		"A - Lara - 0 - 3 - S - 0\n";

	EXPECT_EQ(output, treasureMap.getSimulationResult());
}

TEST(TreasureMap, SpawnOnMountain) {
	TreasureMap treasureMap;
	std::string input = "C - 3 - 4\n"
		"M - 1 - 0\n"
		"M - 2 - 1\n"
		"T - 0 - 3 - 2\n"
		"T - 1 - 3 - 3\n"
		"A - Lara - 1 - 0 - S - AADADAGGA\n";
	treasureMap.runSimulation(input);

	std::string output = "C - 3 - 4\n"
		"M - 1 - 0\n"
		"M - 2 - 1\n"
		"T - 0 - 3 - 2\n"
		"T - 1 - 3 - 3\n";

	EXPECT_EQ(output, treasureMap.getSimulationResult());
}

TEST(TreasureMap, OutOfBounds) {
	TreasureMap treasureMap;
	std::string input = "C - 3 - 4\n"
		"M - 1 - 0\n"
		"M - 2 - 1\n"
		"T - 0 - 3 - 2\n"
		"T - 1 - 3 - 3\n"
		"A - Lara - 0 - 0 - N - AAAGAAA\n"
		"A - Toto - 2 - 3 - S - AAAGAAA\n";
	treasureMap.runSimulation(input);

	std::string output = "C - 3 - 4\n"
		"M - 1 - 0\n"
		"M - 2 - 1\n"
		"T - 0 - 3 - 2\n"
		"T - 1 - 3 - 3\n"
		"A - Lara - 0 - 0 - W - 0\n"
		"A - Toto - 2 - 3 - E - 0\n";

	EXPECT_EQ(output, treasureMap.getSimulationResult());
}

TEST(TreasureMap, CrossMountain) {
	TreasureMap treasureMap;
	std::string input = "C - 3 - 4\n"
		"M - 1 - 0\n"
		"M - 2 - 1\n"
		"T - 0 - 3 - 2\n"
		"T - 1 - 3 - 3\n"
		"A - Lara - 0 - 0 - E - AAA\n";
	treasureMap.runSimulation(input);

	std::string output = "C - 3 - 4\n"
		"M - 1 - 0\n"
		"M - 2 - 1\n"
		"T - 0 - 3 - 2\n"
		"T - 1 - 3 - 3\n"
		"A - Lara - 0 - 0 - E - 0\n";

	EXPECT_EQ(output, treasureMap.getSimulationResult());
}

TEST(TreasureMap, Comments) {
	TreasureMap treasureMap;
	std::string input = "C - 3 - 4\n"
		"M - 1 - 0\n"
		"M - 2 - 1\n"
		"# M - 2 - 2\n"
		"#M - 1 - 1\n"
		"T - 0 - 3 - 2\n"
		"T - 1 - 3 - 3\n"
		"#T - 2 - 3 - 3\n"
		"#        T - 1 - 4 - 3\n"
		"A - Lara - 1 - 1 - S - AADADAGGA\n";
	treasureMap.runSimulation(input);

	std::string output = "C - 3 - 4\n"
		"M - 1 - 0\n"
		"M - 2 - 1\n"
		"T - 1 - 3 - 2\n"
		"A - Lara - 0 - 3 - S - 3\n";

	EXPECT_EQ(output, treasureMap.getSimulationResult());
}

TEST(TreasureMap, CrossAdventurer) {
	TreasureMap treasureMap;
	std::string input = "C - 3 - 4\n"
		"M - 1 - 0\n"
		"M - 2 - 1\n"
		"T - 0 - 3 - 2\n"
		"T - 1 - 3 - 3\n"
		"A - Lara - 0 - 0 - S - AAAAAA\n"
		"A - Toto - 0 - 1 - N - AAAAAA\n";
	treasureMap.runSimulation(input);

	std::string output = "C - 3 - 4\n"
		"M - 1 - 0\n"
		"M - 2 - 1\n"
		"T - 0 - 3 - 2\n"
		"T - 1 - 3 - 3\n"
		"A - Lara - 0 - 0 - S - 0\n"
		"A - Toto - 0 - 1 - N - 0\n";

	EXPECT_EQ(output, treasureMap.getSimulationResult());
}

TEST(TreasureMap, GivenTestFromFile) {
	TreasureMap treasureMap;
	treasureMap.runSimulation("input.txt");

	std::string output = "C - 3 - 4\n"
		"M - 1 - 0\n"
		"M - 2 - 1\n"
		"T - 1 - 3 - 2\n"
		"A - Lara - 0 - 3 - S - 3\n";

	EXPECT_EQ(output, treasureMap.getSimulationResult());
}

TEST(TreasureMap, GivenTestToFile) {
	TreasureMap treasureMap;
	treasureMap.runSimulation("input.txt");

	treasureMap.outputToFile("output.txt");
	std::string output = "C - 3 - 4\n"
		"M - 1 - 0\n"
		"M - 2 - 1\n"
		"T - 1 - 3 - 2\n"
		"A - Lara - 0 - 3 - S - 3\n";

	std::ifstream file("output.txt");

	if (!file.is_open())
	{
		FAIL();
		return;
	}
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	EXPECT_EQ(output, buffer.str());
}