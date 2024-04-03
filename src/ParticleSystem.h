#pragma once

#include <vector>


class ParticleSystem
{

	struct vec2D {
		float x, y;
	};

public:
	ParticleSystem();
	ParticleSystem(unsigned int num_particles);

private:

	std::vector<vec2D> positions;
	std::vector<vec2D> velocities; 

};

