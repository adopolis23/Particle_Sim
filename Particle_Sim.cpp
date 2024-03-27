#include <SDL.h>
#undef main

#include "Window.h"

int main()
{

	sim::Window* window = new sim::Window(720, 480);
	
	for (int i = 0; i < 1e10; i++) {
		std::cout << (i) << "\n";
	}

	return 0;
}

