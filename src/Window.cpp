#include "Window.h"

sim::Window::Window(unsigned int width, unsigned int height)
	:m_Window(nullptr),m_textTexture(nullptr), m_textSurface(nullptr), m_Renderer(nullptr), m_Width(width), m_Height(height), m_mainBuffer(nullptr)
{
	this->init();
}



bool sim::Window::init() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Could not initialize SDL graphics" << std::endl;
		return false;
	}
	std::cout << "SDL Graphics Initialized Successfully" << std::endl;


	m_Window = SDL_CreateWindow("Particle Simulator",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_Width, m_Height,
		SDL_WINDOW_SHOWN);
	if (!m_Window) {
		SDL_Log("Could not create the window. ");
		SDL_Log("%s", SDL_GetError());
		SDL_Quit();
		return false;
	}
	std::cout << "SDL Window Initialized Successfully" << std::endl;

	m_Renderer = SDL_CreateRenderer(m_Window, -1,
		SDL_RENDERER_PRESENTVSYNC);

	if (!m_Renderer) {
		SDL_Log("Could not create the renderer. ");
		SDL_Log("%s", SDL_GetError());
		SDL_Quit();
		return false;
	}
	std::cout << "SDL Renderer Initialized Successfully" << std::endl;


	m_Texture = SDL_CreateTexture(m_Renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_STATIC, m_Width, m_Height);

	if (!m_Texture) {
		SDL_Log("Could not create the texture. ");
		SDL_Log("%s", SDL_GetError());
		SDL_DestroyRenderer(m_Renderer);
		SDL_DestroyWindow(m_Window);
		SDL_Quit();
		return false;
	}

	SDL_Log("SDL Texture Initialized Successfully");



	m_mainBuffer = new Uint32[m_Width * m_Height];

	return true;
}




int sim::Window::handleEvents()
{
	SDL_Event event;

	int action = -1;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			action = Action::QUIT;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_LEFT:
				action = Action::LEFT;
				break;
			case SDLK_RIGHT:
				action = Action::RIGHT;
				break;
			case SDLK_DOWN:
				action = Action::DOWN;
				break;
			case SDLK_UP:
				action = Action::UP;
				break;
			}
			break;
		}
	}

	return action;
}





void sim::Window::clear() {
	memset(m_mainBuffer, 0, m_Width * m_Height * sizeof(Uint32));
}

void sim::Window::update() {
	SDL_UpdateTexture(m_Texture, NULL, m_mainBuffer, m_Width * sizeof(Uint32));
	SDL_RenderClear(m_Renderer);
	SDL_RenderCopy(m_Renderer, m_Texture, NULL, NULL);
	SDL_RenderPresent(m_Renderer);
}



void sim::Window::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {
	
	//input checking
	if (x <= 0 || x >= m_Width || y >= m_Height || y <= 0) {
		return; 
	}

	Uint32 new_color = (Uint32)0;

	new_color = new_color + red;
	new_color <<= 8;
	new_color = new_color + green;
	new_color <<= 8;
	new_color = new_color + blue;
	new_color <<= 8;
	new_color = new_color + 0xff;

	m_mainBuffer[y * m_Width + x] = new_color;

}

//Destructor Function
//free all memory on heap using SDL destroy funcitons
sim::Window::~Window() {
	SDL_DestroyWindow(m_Window);
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyTexture(m_Texture);
	delete[] m_mainBuffer;
}
