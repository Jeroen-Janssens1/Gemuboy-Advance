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

void Test16BitReadWriteEWRAM()
{
	Memory* memory = new Memory();
	memory->WriteWord(GBA::EWRAM_START_ADDRESS, 0x1234);
	assert(memory->ReadWord(GBA::EWRAM_START_ADDRESS) == 0x1234);
	// also ensure the ReadByte returns correct lower and upper values
	assert(memory->ReadByte(GBA::EWRAM_START_ADDRESS) == 0x34);
	assert(memory->ReadByte(GBA::EWRAM_START_ADDRESS + 1) == 0x12);
	std::cout << "16-bit Read/Write test passed!\n";
	delete memory;
}

void Test32BitReadWriteEWRAM()
{
	Memory* memory = new Memory();
	memory->WriteDWord(GBA::EWRAM_START_ADDRESS, 0x12345678);
	assert(memory->ReadDWord(GBA::EWRAM_START_ADDRESS) == 0x12345678);
	// also ensure the ReadByte returns correct lower and upper values
	assert(memory->ReadByte(GBA::EWRAM_START_ADDRESS) == 0x78);
	assert(memory->ReadByte(GBA::EWRAM_START_ADDRESS + 1) == 0x56);
	assert(memory->ReadByte(GBA::EWRAM_START_ADDRESS + 2) == 0x34);
	assert(memory->ReadByte(GBA::EWRAM_START_ADDRESS + 3) == 0x12);
	std::cout << "32-bit Read/Write test passed!\n";
	delete memory;
}

void RunMemoryTests()
{
	TestOutput::WriteTestTitle("Memory Tests");
	std::cout << "Running memory tests, please wait...\n\n";
	TestEWRAM();
	TestIWRAM();
	Test16BitReadWriteEWRAM();
	Test32BitReadWriteEWRAM();
	TestEWRAMMirroring();
	TestIWRAMMirroring();
	std::cout << "All memory tests passed successfully!\n\n";
}