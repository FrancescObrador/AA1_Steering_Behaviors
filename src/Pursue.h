#pragma once
#include "Seek.h"

class Pursue : public Seek
{
public:
	Pursue();
	~Pursue();
	void applySteeringForce(Agent* agent, float dtime);
	Vector2D calculatePursueForce(Vector2D targetPosition, Vector2D targetVelocity, Agent* agent);
};
