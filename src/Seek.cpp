#include "Seek.h"

Seek::Seek(float _priorityWeight) : SteeringBehavior(_priorityWeight)
{
}

Seek::~Seek()
{
}

void Seek::applySteeringForce(Agent *agent, float dtime)
{
	Vector2D steeringForce = calculateSteeringForce(agent);
	Vector2D acceleration = steeringForce / agent->getMass();
	Vector2D velocity = agent->getVelocity() + acceleration * dtime;
	velocity = Vector2D::Truncate(velocity, agent->getMaxVelocity());

	agent->setVelocity(velocity);
	agent->setPosition(agent->getPosition() + velocity * dtime);
}

Vector2D Seek::calculateSteeringForce(Agent* agent)
{
	//seek direction
	Vector2D desiredVelocity = agent->getTarget() - agent->getPosition();
	desiredVelocity.Normalize();

	// direction to velocity
	desiredVelocity *= agent->getMaxVelocity();
	Vector2D seekForce = (desiredVelocity - agent->getVelocity());
	seekForce /= agent->getSpeed();
	return seekForce * agent->getMaxForce() * priorityWeight;
}