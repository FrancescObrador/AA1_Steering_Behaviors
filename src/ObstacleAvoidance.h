#pragma once
#include "Agent.h"

class ObstacleAvoidance :
	public Agent::SteeringBehavior
{
private:
	std::vector<Obstacle>* obstacles;
	
public:
	ObstacleAvoidance(std::vector<Obstacle>* _obstacles, float _priorityWeight);
	~ObstacleAvoidance();
	void applySteeringForce(Agent *agent, float dtime);
	Vector2D calculateSteeringForce(Agent* agent);
};