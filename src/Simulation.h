#pragma once
#include "Window.h"

class Simulation
{

public:
	Simulation();

	~Simulation();

	void Start();
	void HandleInput();
	void Update();
	void Render();

private:
	
	sim::Window* m_Window;

	Uint16 m_Width;
	Uint16 m_Height;

	bool isRunning;

	unsigned int blockSize;
	unsigned int simWidth;
	unsigned int simHeight;

	unsigned int targetFPS;

	Uint8* m_SimStates;

};

