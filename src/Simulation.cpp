#include "Simulation.h"

Simulation::Simulation()
	:m_Width(700), m_Height(460), m_Window(nullptr), isRunning(false), 
	m_SimStates(nullptr), blockSize(10), targetFPS(60)
{

	//check that block size divides height and width
	if (m_Width % blockSize != 0 || m_Height % blockSize != 0) {
		throw std::invalid_argument("Width and Height must be divisble by block size.");
	}

	m_Window = new sim::Window(m_Width, m_Height);

	//initialize and set simstates to 0
	m_SimStates = new Uint8[(m_Width / blockSize) * (m_Height / blockSize)];
	memset(m_SimStates, 0, (m_Width / blockSize) * (m_Height / blockSize) * sizeof(Uint8));

	//caluculate the simulation dimentions
	simWidth = m_Width / blockSize;
	simHeight = m_Height / blockSize;


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
		placeSand(b.x, b.y);
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
	
}


void Simulation::Render()
{
	//clears the screen - sets the main buffer to all zero
	m_Window->clear();
	
	/*for (int x_block = 0; x_block < simWidth; x_block++) {
		for (int y_block = 0; y_block < simHeight; y_block++) {
			if (m_SimStates[x_block + y_block * simWidth] == 0) {
				continue;
			}
			else if (m_SimStates[x_block + y_block * simWidth] == 1) {
				m_Window->fillRect(x_block*blockSize, y_block*blockSize, blockSize, blockSize, 0xFF, 0xFF, 0xFF);
			}
		}
	}*/


	//copies the buffer contents to the window renderer - pushes changes maid by render functions to the screen
	m_Window->update();
}

void Simulation::placeSand(const unsigned int& x, const unsigned int& y)
{
	int block_x = (int)(x / blockSize);
	int block_y = (int)(y / blockSize);

	m_SimStates[block_x + block_y * simWidth] = 1;
}





Simulation::~Simulation()
{
}
