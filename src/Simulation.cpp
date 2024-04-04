#include "Simulation.h"

Simulation::Simulation()
	:m_Width(720), m_Height(480), m_Window(nullptr), isRunning(false), 
	targetFPS(120)
{

	m_Window = new sim::Window(m_Width, m_Height);

	m_ParticleSystem = new ParticleSystem(200, m_Width, m_Height);

	gravity = false;

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

		//gravity = !gravity; 

		m_ParticleSystem->handleMouseClick(b.x, b.y);
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

	//apply gravity
	if (gravity)
		m_ParticleSystem->applyAccelerationAll(0.0, 0.3);
}


void Simulation::Render()
{
	//clears the screen - sets the main buffer to all zero
	m_Window->clear();
	
	//render the density heatmap
	m_ParticleSystem->drawDensityHeatMap(m_Window, 10);
 
	//render particles
	m_ParticleSystem->renderParticles(m_Window);

	


	//copies the buffer contents to the window renderer - pushes changes maid by render functions to the screen
	m_Window->update();
}









Simulation::~Simulation()
{
}
