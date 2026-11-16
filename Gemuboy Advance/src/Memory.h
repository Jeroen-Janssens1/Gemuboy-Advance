#pragma once

#include <array>
#include <cstdint>
#include <vector>

/*
* The memory in the GBA is addressed differently depending on which memory region
* you are accessing.
*/

class Memory final
{
public:
	Memory();

	uint8_t ReadByte(uint32_t address);
	uint16_t ReadWord(uint32_t address);
	uint32_t ReadDWord(uint32_t address);

	void WriteByte(uint32_t address, uint8_t value);
	void WriteWord(uint32_t address, uint16_t value);
	void WriteDWord(uint32_t address, uint32_t value);

	bool LoadROM(const char* filepath);

	bool LoadBIOS(const char* filepath);

private:
	// GIM (General Internal Memory)
	std::array<uint8_t, 0x4000> m_BIOS{}; // 16KB of BIOS memory
	std::array<uint8_t, 0x40000> m_EWRAM{}; // 256KB of EWRAM
	std::array<uint8_t, 0x80000> m_IWRAM{}; // 32KB of IWRAM
	std::array<uint8_t, 0x400> m_IORegisters{}; // 1KB of IO Registers

	// IDM (Internal Display Memory)
	std::array<uint8_t, 0x400> m_PaletteRAM{}; // 1KB of Palette RAM
	std::array<uint8_t, 0x18000> m_VRAM{}; // 96KB of VRAM
	std::array<uint8_t, 0x400> m_OAM{}; // 1KB of OAM (Object Attribute Memory)

	// external / Game Pak memory
	std::vector<uint8_t> m_ROM{}; // Game Pak ROM (up to 32MB x3)
	std::vector<uint8_t> m_SRAM{}; // Game Pak SRAM (up to 64KB)

	// address decoding
	uint8_t* GetMemoryPointer(uint32_t address);
};

