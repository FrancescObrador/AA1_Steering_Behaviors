#pragma once
#include "Agent.h"

class Seek :
	public Agent::SteeringBehavior
{
public:
	Seek();
	~Seek();
	virtual void applySteeringForce(Agent *agent, float dtime);
	Vector2D calculateSeekForce(Vector2D targetPosition, Agent* agent);
};
