#pragma once
#include "Agent.h"

class Flee :
	public Agent::SteeringBehavior
{
public:
	Flee(float _priorityWeight);
	~Flee();
	void applySteeringForce(Agent *agent, float dtime);
	Vector2D calculateSteeringForce(Agent* agent);
};
