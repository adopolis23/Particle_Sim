#include <SDL.h>
#undef main

#include "Window.h"
#include "Simulation.h"

int main()
{
	Simulation* sim = new Simulation();
	sim->Start();

	return 0;
}

