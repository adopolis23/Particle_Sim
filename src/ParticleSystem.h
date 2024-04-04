#pragma once

#include <vector>
#include <iostream>
#include <cstdlib>
#include <cmath>


#include "Window.h"


class ParticleSystem
{

	struct vec2D {
		float x, y;

		vec2D() {
			x = 0;
			y = 0;
		};

		vec2D(float x1, float y1) {
			x = x1;
			y = y1;
		}

		float mag() {
			return std::sqrt(x*x + y*y);
		}

		vec2D operator- (const vec2D& v1) {
			return vec2D(x-v1.x, y-v1.y);
		};
	};

public:
	ParticleSystem();
	ParticleSystem(unsigned int num_particles, unsigned int width, unsigned int height);

	void updateParticles();
	void applyAcceleration(float ax, float ay);
	void renderParticles(sim::Window* window);

	void handleMouseClick(int x, int y);

	float sampleDensity(vec2D sample_point);
	void drawDensityHeatMap(sim::Window* window, int block_size);

	vec2D CalculateDensityGradientDifferential(vec2D sample_point);

private:

	float smoothingKernel(float kernel_radius, float x);
	

	unsigned int numParticles; 
	unsigned int particleSize; 
	float collisionDampingFactor;
	float gradientScaleFactor;
	int smoothingKernelSize;

	unsigned int simWidth;
	unsigned int simHeight;

	std::vector<vec2D> positions;
	std::vector<vec2D> velocities; 
	std::vector<vec2D> accelerations;


};

