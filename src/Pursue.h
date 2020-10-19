#pragma once
#include "Agent.h"
#include "Seek.h"

class Pursue : public Agent::SteeringBehavior
{
public:
	Pursue(float _priorityWeight);
	~Pursue();
	void applySteeringForce(Agent* agent, float dtime);
	Vector2D calculateSteeringForce(Agent *agent);
};
