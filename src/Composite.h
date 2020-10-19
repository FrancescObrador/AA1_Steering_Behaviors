#pragma once
#include "Agent.h"

class Composite :
	public Agent::SteeringBehavior
{
private:
	std::vector<SteeringBehavior*>* steeringBehaviors;

public:
	Composite(std::vector<SteeringBehavior*>* _steeringBehaviors, float _priorityWeight);
	~Composite();
	void applySteeringForce(Agent *agent, float dtime);
	Vector2D calculateSteeringForce(Agent* agent);
};
