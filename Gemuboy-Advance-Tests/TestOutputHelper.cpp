#include "TestOutputHelper.h"
#include <iostream>
#include <iomanip>

void TestOutput::WriteTestTitle(const char* testName)
{
	int padding = (TITLE_WIDTH - strlen(testName)) / 2;
	int stringLength = strlen(testName);
	std::cout << std::string(TITLE_WIDTH, '-') << '\n';
	std::cout << "|" << std::string(padding, ' ') << testName 
		<< std::string(TITLE_WIDTH - padding - stringLength - 2, ' ') << "|\n";
	std::cout << std::string(TITLE_WIDTH, '-') << "\n\n";
}