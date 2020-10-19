#include "Flee.h"

Flee::Flee(float _priorityWeight) : SteeringBehavior(_priorityWeight)
{
}

Flee::~Flee()
{
}

void Flee::applySteeringForce(Agent *agent, float dtime)
{
	Vector2D steeringForce = calculateSteeringForce(agent);
	Vector2D acceleration = steeringForce / agent->getMass();
	Vector2D velocity = agent->getVelocity() + acceleration * dtime;
	velocity = Vector2D::Truncate(velocity, agent->getMaxVelocity());

	agent->setVelocity(velocity);
	agent->setPosition(agent->getPosition() + velocity * dtime);
}

Vector2D Flee::calculateSteeringForce(Agent* agent)
{
	//seek direction
	Vector2D desiredVelocity = agent->getPosition() - agent->getTarget();
	desiredVelocity.Normalize();

	// direction to velocity
	desiredVelocity *= agent->getMaxVelocity();
	Vector2D seekForce = (desiredVelocity - agent->getVelocity());
	seekForce /= agent->getSpeed();
	return seekForce * agent->getMaxForce() * priorityWeight;
}