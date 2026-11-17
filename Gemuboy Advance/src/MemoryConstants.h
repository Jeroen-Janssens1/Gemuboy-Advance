#pragma once

#include <cstdint>

namespace GBA
{
	constexpr uint32_t BIOS_START_ADDRESS = 0x00000000;
	constexpr uint32_t BIOS_SIZE = 0x4000;

	constexpr uint32_t EWRAM_START_ADDRESS = 0x02000000;
	constexpr  uint32_t EWRAM_SIZE = 0x40000;

	constexpr uint32_t IWRAM_START_ADDRESS = 0x03000000;
	constexpr  uint32_t IWRAM_SIZE = 0x8000;

	constexpr uint32_t IO_START_ADDRESS = 0x04000000;
	constexpr uint32_t IO_SIZE = 0x400;

	constexpr uint32_t PALETTE_START_ADDRESS = 0x05000000;
	constexpr uint32_t PALETTE_SIZE = 0x400;

	constexpr uint32_t VRAM_START_ADDRESS = 0x06000000;
	constexpr uint32_t VRAM_SIZE = 0x18000;

	constexpr uint32_t OAM_START_ADDRESS = 0x07000000;
	constexpr uint32_t OAM_SIZE = 0x400;

	constexpr  uint32_t ROM_START_ADDRESS = 0x08000000;
	constexpr uint32_t ROM_SIZE = 0x2000000;

	constexpr uint32_t SRAM_START_ADDRESS = 0x0E000000;
	constexpr uint32_t SRAM_SIZE = 0x10000;
}