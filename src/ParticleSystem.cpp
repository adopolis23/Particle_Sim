#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
	numParticles = 0;
	particleSize = 1;
	collisionDampingFactor = 0.9;
}

ParticleSystem::ParticleSystem(unsigned int num_particles, unsigned int width, unsigned int height) {
	simWidth = width;
	simHeight = height; 
	
	numParticles = num_particles;
	particleSize = 2;
	collisionDampingFactor = 0.8;
	gradientScaleFactor = 0.004;
	smoothingKernelSize = 60;

	int particlesPerRow = (int)sqrt(numParticles);
	int numRows = numParticles / particlesPerRow;

	//initialize particles random location
	for (int i = 0; i < num_particles; i++) {
		vec2D position;
		vec2D velocity;
		vec2D acceleration; 

		//position.x = 1 + (rand() % width);

		position.x = (i%particlesPerRow)  * (particleSize * 2) + width/2-(particlesPerRow * particleSize);
		position.y = (int)(i / numRows) * (particleSize * 2) + height/2-(numRows * particleSize);

		//velocity.x = (((double)rand()) / RAND_MAX - 0.5) * 5;
		//velocity.y = (((double)rand()) / RAND_MAX - 0.5) * 5;
		velocity.x = 0;
		velocity.y = 0;

		acceleration.x = 0;
		acceleration.y = 0;

		velocities.push_back(velocity);
		positions.push_back(position);
		accelerations.push_back(acceleration);
	}

}

void ParticleSystem::updateParticles()
{	
	for (int i = 0; i < numParticles; i++) {
		positions[i].x += velocities[i].x;
		positions[i].y += velocities[i].y;

		vec2D grad = CalculateDensityGradientDifferential(positions[i]);

		velocities[i].x += grad.x * -gradientScaleFactor;//accelerations[i].x;
		velocities[i].y += grad.y * -gradientScaleFactor;//accelerations[i].y;



		//colissions with walls
		if ((positions[i].x > simWidth-particleSize)) {
			velocities[i].x = velocities[i].x * -1 * collisionDampingFactor;
			positions[i].x = simWidth - particleSize;
		}

		if ((positions[i].x <= 0)) {
			velocities[i].x = velocities[i].x * -1 * collisionDampingFactor;
			positions[i].x = 0;
		}


		if ((positions[i].y > simHeight-particleSize)) {
			velocities[i].y = velocities[i].y * -1 * collisionDampingFactor;
			positions[i].y = simHeight - particleSize;
		}
		if (positions[i].y <= 0) {
			velocities[i].y = velocities[i].y * -1 * collisionDampingFactor;
			positions[i].y = 0;
		}
	}
}



void ParticleSystem::applyAcceleration(float ax, float ay)
{
	for (int i = 0; i < numParticles; i++) {
		velocities[i].x += ax;
		velocities[i].y += ay;
	}
}



void ParticleSystem::renderParticles(sim::Window* window) {
	for (int i = 0; i < numParticles; i++) {
		window->fillCircle(positions[i].x, positions[i].y, particleSize, 0xFF, 0xFF, 0xFF);
	}

}



void ParticleSystem::handleMouseClick(int x, int y)
{
	vec2D grad = CalculateDensityGradientDifferential(vec2D(x, y));
	std::cout << grad.x << " " << grad.y << "\n";
}



//returns the value of the smothing kernel (k^2 - x^2)^3 
float ParticleSystem::smoothingKernel(float kernel_radius, float x)
{
	//float volume = 3.14159 * (pow(kernel_radius, 8) / 4);
	float volume = 3.14159 * (pow(kernel_radius, 8) / 4);

	/*
	float val = (kernel_radius * kernel_radius) - (x * x);
	if (val < 0) {
		val = 0;
	}

	return val * val * val;*/

	float val = kernel_radius - x;
	if (val < 0) {
		val = 0;
	}
	return val;
}

float ParticleSystem::sampleDensity(vec2D sample_point)
{
	float density = 0;
	float distance = 0;
	float influence;

	for (int i = 0; i < numParticles; i++) {
		distance = (positions[i] - sample_point).mag();
		influence = smoothingKernel(smoothingKernelSize, distance);
		density += influence; 
	}

	return density;
}

void ParticleSystem::drawDensityHeatMap(sim::Window* window, int block_size) {

	float density;

	for (int y = 0; y < simHeight / block_size; y++) {
		for (int x = 0; x < simWidth / block_size; x++) {
			
			density = sampleDensity(vec2D(x* block_size, y* block_size));

			if (density > 256) {
				density = 0xFF;
			}

			window->fillRect(x*block_size, y*block_size, block_size, block_size, density, 0x00, 0xFF - density);

		}
	}
}

ParticleSystem::vec2D ParticleSystem::CalculateDensityGradientDifferential(ParticleSystem::vec2D sample_point)
{
	//probably should be less than 1 but whatever
	float delta = 1.0;

	float deltaX = sampleDensity(vec2D(sample_point.x + delta, sample_point.y)) - sampleDensity(sample_point);
	float deltaY = sampleDensity(vec2D(sample_point.x, sample_point.y + delta)) - sampleDensity(sample_point);

	vec2D gradient = vec2D(deltaX/delta, deltaY/delta);

	return gradient;
}
