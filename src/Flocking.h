#pragma once
#include <vector>
#include "Agent.h"

class Flocking : public Agent::SteeringBehavior
{
private:
	std::vector<Agent*>* flockingAgents;
	//std::vector<Obstacle>* obstacles;
	float NEIGHBOR_RADIUS = 50;

	float K_SEPARATION_FORCE = 4000;
	float K_COHESION_FORCE = 50;
	float K_ALIGNMENT_FORCE = 1;

	float K_MAX_FLOCKING_FORCE = 100;

public:
	Flocking(std::vector<Agent*>* flockingAgents, float _priorityWeight);
	~Flocking();
	virtual void applySteeringForce(Agent* agent, float dtime);
	Vector2D calculateSteeringForce(Agent* agent);
};
