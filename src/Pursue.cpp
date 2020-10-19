#include "Pursue.h"

Pursue::Pursue(float _priorityWeight) : SteeringBehavior(_priorityWeight)
{
}

Pursue::~Pursue()
{
}

void Pursue::applySteeringForce(Agent* agent, float dtime)	//TODO: solve this
{
	Vector2D steeringForce = calculateSteeringForce(agent);

	Vector2D acceleration = steeringForce / agent->getMass();
	Vector2D velocity = agent->getVelocity() + acceleration * dtime;
	velocity = Vector2D::Truncate(velocity, agent->getMaxVelocity());
	agent->setVelocity(velocity);
	agent->setPosition(agent->getPosition() + velocity * dtime);
}

Vector2D Pursue::calculateSteeringForce(Agent *agent)
{
	float velocity = agent->getVelocity().Length();
	Seek* auxSeek = new Seek(priorityWeight);
	if (velocity != 0)
	{
		float t = Vector2D::Distance(agent->getPosition(), agent->getTargetAgent()->getPosition()) / velocity;
		Vector2D predictedTarget = agent->getTargetAgent()->getPosition() + (agent->getTargetAgent()->getVelocity() * t);
		
		Agent* fakeTarget = new Agent(*agent);
		fakeTarget->setTarget(predictedTarget);

		return auxSeek->calculateSteeringForce(fakeTarget); //.calculateSeekForce(predictedTarget, agent);
	}
	else
	{
		return auxSeek->calculateSteeringForce(agent);
	}
}