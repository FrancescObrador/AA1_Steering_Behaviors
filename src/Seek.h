#pragma once
#include "Agent.h"

class Seek :
	public Agent::SteeringBehavior
{
protected:
	float K_OBSTACLE_AVOIDANCE_PRIORITY = 100;
	std::vector<Obstacle>* obstacles = new std::vector<Obstacle>();
public:
	Seek();
	Seek(std::vector<Obstacle>* obstacles);
	~Seek();
	virtual void applySteeringForce(Agent *agent, float dtime);
	Vector2D calculateSeekForce(Vector2D targetPosition, Agent* agent);
	Vector2D obstacleAvoidanceForce(Agent* agent, std::vector<Obstacle>* obstacles);
};
