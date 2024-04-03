#pragma once

#include <vector>
#include <iostream>
#include <cstdlib>

#include "Window.h"


class ParticleSystem
{

	struct vec2D {
		float x, y;
	};

public:
	ParticleSystem();
	ParticleSystem(unsigned int num_particles, unsigned int width, unsigned int height);

	void updateParticles();
	void applyAcceleration(float ax, float ay);
	void renderParticles(sim::Window* window);
private:

	unsigned int numParticles; 
	unsigned int particleSize; 
	float collisionDampingFactor;

	unsigned int simWidth;
	unsigned int simHeight;

	std::vector<vec2D> positions;
	std::vector<vec2D> velocities; 
	std::vector<vec2D> accelerations;


};

