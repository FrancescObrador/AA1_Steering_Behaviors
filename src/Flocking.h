#pragma once
#include <vector>
#include "Pursue.h"

class Flocking : public Pursue
{
private:
	std::vector<Agent*>* flockingAgents;
	//std::vector<Obstacle>* obstacles;
	float NEIGHBOR_RADIUS = 50;

	float K_SEPARATION_FORCE = 400;
	float K_COHESION_FORCE = 50;
	float K_ALIGNMENT_FORCE = 1;

	float K_MAX_FLOCKING_FORCE = 100;

public:
	Flocking();
	Flocking(std::vector<Agent*>* flockingAgents, std::vector<Obstacle>* obstacles);
	~Flocking();
	virtual void applySteeringForce(Agent* agent, float dtime);
	Vector2D calculateFlockingForce(Agent* agent);
};
