#pragma once
#include "Agent.h"

class Seek : public Agent::SteeringBehavior
{
protected:
	
public:
	Seek(float _priorityWeight);
	~Seek();
	virtual void applySteeringForce(Agent *agent, float dtime);
	Vector2D calculateSteeringForce(Agent* agent);
};
