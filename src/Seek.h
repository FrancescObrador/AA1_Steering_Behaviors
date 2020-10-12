#pragma once
#include "Agent.h"

class Seek :
	public Agent::SteeringBehavior
{
public:
	Seek();
	~Seek();
	void applySteeringForce(Agent *agent, float dtime);
	static Vector2D calculateSeekForce(Vector2D targetPosition, Agent* agent);
};
