#include "Memory.h"
#include "MemoryTests.h"
#include "TestOutputHelper.h"
#include <cassert>
#include <iostream>

void TestEWRAM()
{
	Memory* memory = new Memory();

	memory->WriteByte(GBA::EWRAM_START_ADDRESS, 0x42);
	
	assert(memory->ReadByte(GBA::EWRAM_START_ADDRESS) == 0x42);
	std::cout << "Basic Read/Write EWRAM test passed!\n";
	delete memory;
}

void TestIWRAM()
{
	Memory* memory = new Memory();
	memory->WriteByte(GBA::IWRAM_START_ADDRESS, 0xAB);

	assert(memory->ReadByte(GBA::IWRAM_START_ADDRESS) == 0xAB);
	std::cout << "Basic Read/Write IWRAM test passed!\n";
	delete memory;
}

void TestEWRAMMirroring()
{
	Memory* memory = new Memory();
	memory->WriteByte(GBA::EWRAM_START_ADDRESS, 0x42);
	// EWRAM is mirrored every 256KB, so writing to the start should reflect in the mirrored address
	assert(memory->ReadByte(GBA::EWRAM_START_ADDRESS + GBA::EWRAM_SIZE) == 0x42);
	assert(memory->ReadByte(GBA::EWRAM_START_ADDRESS + 16 * GBA::EWRAM_SIZE) == 0x42);
	std::cout << "EWRAM mirroring test passed!\n";
	delete memory;
}

void TestIWRAMMirroring()
{
	Memory* memory = new Memory();
	memory->WriteByte(GBA::IWRAM_START_ADDRESS, 0xAB);
	// IWRAM is mirrored every 32KB, so writing to the start should reflect in the mirrored address
	assert(memory->ReadByte(GBA::IWRAM_START_ADDRESS + GBA::IWRAM_SIZE) == 0xAB);
	assert(memory->ReadByte(GBA::IWRAM_START_ADDRESS + 16 * GBA::IWRAM_SIZE) == 0xAB);
	std::cout << "IWRAM mirroring test passed!\n";
	delete memory;
}

void RunMemoryTests()
{
	TestOutput::WriteTestTitle("Memory Tests");
	std::cout << "Running memory tests, please wait...\n\n";
	TestEWRAM();
	TestIWRAM();
	TestEWRAMMirroring();
	TestIWRAMMirroring();
	std::cout << "All memory tests passed successfully!" << std::endl;
}