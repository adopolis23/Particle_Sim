#include "Simulation.h"

Simulation::Simulation()
	:m_Width(700), m_Height(460), m_Window(nullptr), isRunning(false), 
	m_SimStates(nullptr), blockSize(10), targetFPS(60)
{

	if (m_Width % blockSize != 0 || m_Height % blockSize != 0) {
		throw std::invalid_argument("Width and Height must be divisble by block size.");
	}

	m_Window = new sim::Window(m_Width, m_Height);

	m_SimStates = new Uint8[(m_Width / blockSize) * (m_Height / blockSize)];
}



void Simulation::Start()
{
	isRunning = true;

	Uint32 framestart, frametime;
	Uint32 framedelay = 1000.0f / this->targetFPS;

	while (isRunning) {
		
		HandleInput();

		framestart = SDL_GetTicks();
		Update();
		frametime = SDL_GetTicks() - framestart;

		if (frametime < framedelay)
			SDL_Delay((framedelay - frametime));


		Render();

	}

}



void Simulation::HandleInput()
{
}


void Simulation::Update()
{
}


void Simulation::Render()
{
	//clears the screen - sets the main buffer to all zero
	m_Window->clear();


	for (int i = 0; i < blockSize; i++) {
		for (int j = 0; j < blockSize; j++) {
			m_Window->setPixel(i, j, 0xFF, 0xFF, 0xFF);
		}
	}


	//copies the buffer contents to the window renderer - pushes changes maid by render functions to the screen
	m_Window->update();
}





Simulation::~Simulation()
{
}
