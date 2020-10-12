#include "Seek.h"

Seek::Seek()
{
}

Seek::~Seek()
{
}

void Seek::applySteeringForce(Agent *agent, float dtime)
{
	// Original alorithm
	/*Vector2D steering = agent->getTarget() - agent->getPosition();
	steering.Normalize();
	agent->setVelocity (steering * agent->getMaxVelocity());
	agent->setPosition (agent->getPosition() + agent->getVelocity() * dtime);*/
	
	Vector2D steeringForce = calculateSeekForce(agent->getTarget(), agent);
	Vector2D acceleration = steeringForce / agent->getMass();
	Vector2D velocity = agent->getVelocity() + acceleration * dtime;
	velocity = Vector2D::Truncate(velocity, agent->getMaxVelocity());

	agent->setVelocity(velocity);
	agent->setPosition(agent->getPosition() + velocity * dtime);
}

Vector2D Seek::calculateSeekForce(Vector2D targetPosition, Agent* agent)
{
	//seek direction
	Vector2D desiredVelocity = targetPosition - agent->getPosition();
	desiredVelocity.Normalize();

	// direction to velocity
	desiredVelocity *= agent->getMaxVelocity();
	Vector2D seekForce = (desiredVelocity - agent->getVelocity());
	seekForce /= agent->getSpeed();
	return seekForce * agent->getMaxForce();
}
