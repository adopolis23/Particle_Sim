#pragma once
#include "Window.h"
#include "ParticleSystem.h"
#include <vector>
#include <iomanip>


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
	void drawDensityHeatMap(int block_size);

	sim::Window* m_Window;

	Uint16 m_Width;
	Uint16 m_Height;

	bool isRunning;

	unsigned int targetFPS;


	ParticleSystem* m_ParticleSystem;
};

