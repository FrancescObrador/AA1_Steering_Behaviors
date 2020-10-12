#include "Pursue.h"

Pursue::Pursue()
{
}

Pursue::~Pursue()
{
}

void Pursue::applySteeringForce(Agent* agent, float dtime)	//TODO: solve this
{
	Vector2D steeringForce = calculatePursueForce(agent->getTargetAgent()->getPosition(), agent->getTargetAgent()->getVelocity(), agent);

	Vector2D acceleration = steeringForce / agent->getMass();
	Vector2D velocity = agent->getVelocity() + acceleration * dtime;
	velocity = Vector2D::Truncate(velocity, agent->getMaxVelocity());
	agent->setVelocity(velocity);
	agent->setPosition(agent->getPosition() + velocity * dtime);
}

Vector2D Pursue::calculatePursueForce(Vector2D targetPosition, Vector2D targetVelocity, Agent* agent)
{
	float velocity = agent->getVelocity().Length(); 

	if (velocity != 0)
	{
		float t = Vector2D::Distance(agent->getPosition(), targetPosition) / velocity;
		Vector2D predictedTarget = targetPosition + (targetVelocity * t);
		return Seek().calculateSeekForce(predictedTarget, agent);
	}
	else 
	{
		return Seek().calculateSeekForce(targetPosition, agent);
	}
}