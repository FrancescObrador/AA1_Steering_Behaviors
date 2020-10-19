#pragma once
#include "Agent.h"

class PerimeterAvoidance :
	public Agent::SteeringBehavior
{
private:
	float K_PRIORITY_PERIMETER_AVOIDANCE = 100;
	float PERIMETER_BORDER = 25;
public:
	PerimeterAvoidance(float _priorityWeight);
	~PerimeterAvoidance();
	void applySteeringForce(Agent *agent, float dtime);
	Vector2D calculateSteeringForce(Agent* agent);
};