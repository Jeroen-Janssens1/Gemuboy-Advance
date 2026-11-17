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

uint16_t Memory::ReadWord(uint32_t address)
{
	uint16_t value = 0;
	// little-endian: read the lower byte first, then the upper byte
	value |= ReadByte(address);
	value |= ReadByte(address + 1) << 8;
	return value;
}

uint32_t Memory::ReadDWord(uint32_t address)
{
	uint32_t value = 0;
	// little-endian: read the lower byte first, then the upper bytes
	value |= ReadByte(address);
	value |= ReadByte(address + 1) << 8;
	value |= ReadByte(address + 2) << 16;
	value |= ReadByte(address + 3) << 24;
	return value;
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

void Memory::WriteWord(uint32_t address, uint16_t value)
{
	// little-endian: write the lower byte first, then the upper byte
	WriteByte(address, value & 0xFF);
	WriteByte(address + 1, (value >> 8) & 0xFF);
}

void Memory::WriteDWord(uint32_t address, uint32_t value)
{
	// little-endian: write the lower byte first, then the upper bytes
	WriteByte(address, value & 0xFF);
	WriteByte(address + 1, (value >> 8) & 0xFF);
	WriteByte(address + 2, (value >> 16) & 0xFF);
	WriteByte(address + 3, (value >> 24) & 0xFF);
}