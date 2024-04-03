#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
	numParticles = 0;
	particleSize = 3;
	collisionDampingFactor = 0.9;
}

ParticleSystem::ParticleSystem(unsigned int num_particles, unsigned int width, unsigned int height) {
	simWidth = width;
	simHeight = height; 
	
	numParticles = num_particles;
	particleSize = 2;
	collisionDampingFactor = 0.9;

	int particlesPerRow = (int)sqrt(numParticles);
	int numRows = numParticles / particlesPerRow;

	//initialize particles random location
	for (int i = 0; i < num_particles; i++) {
		vec2D position;
		vec2D velocity;
		vec2D acceleration; 

		//position.x = 1 + (rand() % width);

		position.x = (i%particlesPerRow)  * (particleSize * 3) + width/2-(particlesPerRow * particleSize);
		position.y = (int)(i / numRows) * (particleSize * 3) + height/2-(numRows * particleSize);

		velocity.x = (((double)rand()) / RAND_MAX - 0.5) * 5;
		velocity.y = (((double)rand()) / RAND_MAX - 0.5) * 5;

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

		velocities[i].x += accelerations[i].x;
		velocities[i].y += accelerations[i].y;



		//colissions with walls
		if ((positions[i].x > simWidth-particleSize || positions[i].x <= 0)) {
			velocities[i].x = velocities[i].x * -1 * collisionDampingFactor;
		}
		if ((positions[i].y > simHeight-particleSize || positions[i].y <= 0)) {
			velocities[i].y = velocities[i].y * -1 * collisionDampingFactor;
			positions[i].y = simHeight - particleSize;
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
