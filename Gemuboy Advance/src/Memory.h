#pragma once

#include <array>
#include <cstdint>
#include <vector>
#include "MemoryConstants.h"

/*
* The memory in the GBA is addressed differently depending on which memory region
* you are accessing. The memory bus layout is as following:
* 
  Region        Bus   Read      Write     Cycles
  BIOS ROM      32    8/16/32   -         1/1/1
  Work RAM 32K  32    8/16/32   8/16/32   1/1/1
  I/O           32    8/16/32   8/16/32   1/1/1
  OAM           32    8/16/32   16/32     1/1/1 Plus 1 cycle if GBA accesses video memory at the same time.
  Work RAM 256K 16    8/16/32   8/16/32   3/3/6 Default waitstate settings, see System Control chapter.
  Palette RAM   16    8/16/32   16/32     1/1/2 Plus 1 cycle if GBA accesses video memory at the same time.
  VRAM          16    8/16/32   16/32     1/1/2 Plus 1 cycle if GBA accesses video memory at the same time.
  GamePak ROM   16    8/16/32   -         5/5/8 Default waitstate settings, see System Control chapter. Separate timings for sequential, and non-sequential accesses.
  GamePak Flash 16    8/16/32   16/32     5/5/8 Default waitstate settings, see System Control chapter. Separate timings for sequential, and non-sequential accesses.
  GamePak SRAM  8     8         8         5     Default waitstate settings, see System Control chapter.
  These show supported read and write widths as well as respective clock cycles for 8, 16 and 32 bit access.
  1 cycle is approx 59.59ns ie a 16.78MHz clock.
  Game Pak SRAM is limited to 8-bit access.

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

	//bool LoadROM(const char* filepath);

	//bool LoadBIOS(const char* filepath);

private:
	// GIM (General Internal Memory)
	std::array<uint8_t, GBA::BIOS_SIZE> m_BIOS{}; // 16KB of BIOS memory
	std::array<uint8_t, GBA::EWRAM_SIZE> m_EWRAM{}; // 256KB of EWRAM
	std::array<uint8_t, GBA::IWRAM_SIZE> m_IWRAM{}; // 32KB of IWRAM
	// IWRAM has 256 bytes reserved for the interrupt vector table, which is located at 0x03007F00-0x03007FFF (including User Stack, which is initially located at 0x03007F00)
	std::array<uint8_t, GBA::IO_SIZE> m_IORegisters{}; // 1KB of IO Registers

	// IDM (Internal Display Memory)
	std::array<uint8_t, GBA::PALETTE_SIZE> m_PaletteRAM{}; // 1KB of Palette RAM
	std::array<uint8_t, GBA::VRAM_SIZE> m_VRAM{}; // 96KB of VRAM
	std::array<uint8_t, GBA::OAM_SIZE> m_OAM{}; // 1KB of OAM (Object Attribute Memory)

	// external / Game Pak memory
	std::vector<uint8_t> m_ROM{}; // Game Pak ROM (up to 32MB x3 (is mirrored 3 times for using different waitstates)
	std::vector<uint8_t> m_SRAM{}; // Game Pak SRAM (up to 64KB)

	// address decoding
	uint8_t* GetMemoryPointer(uint32_t address);
};

