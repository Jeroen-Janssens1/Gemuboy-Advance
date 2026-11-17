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
	// a lot of memory is mirrored!
	switch (address >> 24)
	{
	case 0x02: // EWRAM
		return m_EWRAM[address & GBA::EWRAM_SIZE-1];
	case 0x03: // IWRAM
		return m_IWRAM[address & GBA::IWRAM_SIZE-1];
	case 0x08: // Game Pak ROM (simplified for now)
	case 0x09:
	case 0x0A:
	case 0x0B:
	case 0x0C:
	case 0x0D:
	{
		const uint32_t offset = address & GBA::ROM_SIZE-1; // mask to 32MB. maps all waitstate regions to same ROM data

		if (offset < m_ROM.size())
			return m_ROM[offset];
		return 0;
	}

	default:
		return 0;
	}
}

void Memory::WriteByte(uint32_t address, uint8_t value)
{
	switch (address >> 24)
	{
	case 0x02: // EWRAM
		m_EWRAM[address & GBA::EWRAM_SIZE-1] = value;
		break;
	case 0x03: // IWRAM
		m_IWRAM[address & GBA::IWRAM_SIZE-1] = value;
		break;
		// ROM is read-only. Other regions for later implementation
	default:
		break;
	}
}