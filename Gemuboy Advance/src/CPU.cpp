#include "CPU.h"
#include "Memory.h"
#include "Graphics.h"
#include "Audio.h"
#include "InputHandler.h"
#include <cstdlib>
#include <iostream>

CPU::CPU(Memory* memory, Graphics* graphics, InputHandler* input, Audio* audio)
	: m_pMemory(memory), m_pGraphics(graphics), m_pInput(input), m_pAudio(audio)
{
	
}

void CPU::RunCycle()
{
	
}

void CPU::UpdateTimers(float deltaSeconds)
{
	
}
