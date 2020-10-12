#include "Flee.h"

Flee::Flee()
{
}

Flee::~Flee()
{
}

void Flee::applySteeringForce(Agent *agent, float dtime)
{
	Vector2D steeringForce = calculateFleeForce(agent->getTarget(), agent);
	Vector2D acceleration = steeringForce / agent->getMass();
	Vector2D velocity = agent->getVelocity() + acceleration * dtime;
	velocity = Vector2D::Truncate(velocity, agent->getMaxVelocity());

	agent->setVelocity(velocity);
	agent->setPosition(agent->getPosition() + velocity * dtime);
}

Vector2D Flee::calculateFleeForce(Vector2D targetPosition, Agent* agent)
{
	//seek direction
	Vector2D desiredVelocity = agent->getPosition() - targetPosition;
	desiredVelocity.Normalize();

	// direction to velocity
	desiredVelocity *= agent->getMaxVelocity();
	Vector2D seekForce = (desiredVelocity - agent->getVelocity());
	seekForce /= agent->getSpeed();
	return seekForce * agent->getMaxForce();
}