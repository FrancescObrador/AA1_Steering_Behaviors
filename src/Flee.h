#pragma once
#include "Agent.h"

class Flee :
	public Agent::SteeringBehavior
{
public:
	Flee();
	~Flee();
	void applySteeringForce(Agent *agent, float dtime);
	Vector2D calculateFleeForce(Vector2D targetPosition, Agent* agent);
};
