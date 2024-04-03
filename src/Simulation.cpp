#include "Simulation.h"

Simulation::Simulation()
	:m_Width(700), m_Height(460), m_Window(nullptr), isRunning(false), 
	targetFPS(100)
{

	m_Window = new sim::Window(m_Width, m_Height);

	m_ParticleSystem = new ParticleSystem(1000, m_Width, m_Height);

}



void Simulation::Start()
{
	isRunning = true;

	Uint32 framestart, frametime;
	Uint32 framedelay = 1000.0f / this->targetFPS;

	//main game loop
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


void Simulation::mouseClick(SDL_MouseButtonEvent& b) {
	if (b.button == SDL_BUTTON_LEFT) {
		std::cout << b.x << " " << b.y << "\n";
	}
}


void Simulation::HandleInput()
{
	SDL_Event e;

	while (SDL_PollEvent(&e)) {

		switch (e.type) {
		case SDL_QUIT:
			isRunning = false;
		case SDL_MOUSEBUTTONDOWN:
			mouseClick(e.button);

		default:
			break;
		}

	}
}


void Simulation::Update()
{
	m_ParticleSystem->updateParticles();
	m_ParticleSystem->applyAcceleration(0.0, 0.1);
}


void Simulation::Render()
{
	//clears the screen - sets the main buffer to all zero
	m_Window->clear();
	
	drawDensityHeatMap(1);
	//render particles
	m_ParticleSystem->renderParticles(m_Window);


	//copies the buffer contents to the window renderer - pushes changes maid by render functions to the screen
	m_Window->update();
}


void Simulation::drawDensityHeatMap(int block_size) {

	for (int i = 0; i < m_Height; i++) {
		for (int j = 0; j < m_Width; j++) {
			m_Window->setPixel(j, i, j, i, 0Xff);
		}
	}

}






Simulation::~Simulation()
{
}
