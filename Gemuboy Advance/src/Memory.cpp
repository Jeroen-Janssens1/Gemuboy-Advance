#include "Memory.h"
#include <iostream>
#include <string>
#include <format>
#include <fstream>
#include <vector>

Memory::Memory()
{
	
}

uint8_t Memory::ReadByte(uint32_t address)
{
	// use a shift >> 24 statement in a switch to filter on memory region
	// then use masking to get correct offset into memory region
	// implement different functions for VRAM, etc... for unique memory handling

	return 0;
}