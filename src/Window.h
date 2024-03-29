#pragma once
#include <iostream>
#include "SDL.h"


namespace sim {

	class Window {

	public:
		enum Action { QUIT, UP, DOWN, LEFT, RIGHT };


	public:
		Window(unsigned int width, unsigned int height);
		~Window();


		bool init();
		int handleEvents();

		void clear();
		void update();
		void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
		void fillRect(int x, int y, int width, int height, Uint8 red, Uint8 green, Uint8 blue);

	private:
		SDL_Window* m_Window;
		SDL_Renderer* m_Renderer;
		SDL_Texture* m_Texture;
		SDL_Surface* m_textSurface;
		SDL_Texture* m_textTexture;
		Uint32* m_mainBuffer;

		unsigned int m_Width;
		unsigned int m_Height;
	};

};