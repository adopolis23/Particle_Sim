#pragma once
#include "Window.h"
#include "ParticleSystem.h"
#include <vector>


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
	void mouseClick(SDL_MouseButtonEvent& b);
	void placeSand(const unsigned int& x, const unsigned int& y);
	
	sim::Window* m_Window;

	Uint16 m_Width;
	Uint16 m_Height;

	bool isRunning;

	unsigned int blockSize;
	unsigned int simWidth;
	unsigned int simHeight;

	unsigned int targetFPS;

	Uint8* m_SimStates;

	ParticleSystem m_ParticleSystem;
};

