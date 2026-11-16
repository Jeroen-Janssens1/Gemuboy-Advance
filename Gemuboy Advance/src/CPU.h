#pragma once
// forward-declares to avoid heavy include
class Memory;
class Graphics;
class InputHandler;
class Audio;
class CPU final
{
public:
	CPU(Memory* memory, Graphics* graphics, InputHandler* input, Audio* audio);

	void RunCycle();

	// Timer update (call every frame with delta seconds)
	void UpdateTimers(float deltaSeconds);
	
private:
	unsigned short m_Opcode;
	unsigned short m_Pc{}; // program counter
	Memory* m_pMemory{};
	Graphics* m_pGraphics{};
	InputHandler* m_pInput{};
	Audio* m_pAudio{};

	// Opcode functions

};
