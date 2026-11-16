#pragma once
class Memory final
{
public:
	Memory();
	unsigned char FetchData(unsigned short addr);
	void WriteData(unsigned short addr, unsigned char value);
	// Load a ROM file into memory at the program start address (0x200).
	bool LoadROM(const char* filepath);
	// Push a return address onto the stack. Returns true on success, false if stack is full.
	bool PushStack(unsigned short addr);
	// Pop a return address from the stack. Returns true on success, false if stack is empty.
	bool PopStack(unsigned short &outAddr);

	#ifdef _DEBUG
	void PrintRAM(unsigned short startAddr, unsigned short endAddr); // debug function to print RAM memory to console window to check RAM state
	#endif

private:
	unsigned short m_FontMemOffset = 0x050;
	unsigned char m_Memory[4096]; // our RAM memory
	unsigned short m_Stack[16]; // we store the stack as an array of shorts because this will only hold memory addresses (16 bit values).
	const unsigned char m_StackSize = 16; // the size of the stack (16 addresses)
	unsigned short sp; // the stack pointer
};

