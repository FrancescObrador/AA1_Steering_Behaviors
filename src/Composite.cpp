#include "Composite.h"

Composite::Composite(std::vector<SteeringBehavior*>* _steeringBehaviors, float _priorityWeight) : SteeringBehavior(_priorityWeight)
{
	steeringBehaviors = _steeringBehaviors;
}

Composite::~Composite()
{
}

void Composite::applySteeringForce(Agent *agent, float dtime)
{
	Vector2D steeringForce = calculateSteeringForce(agent);

	Vector2D acceleration = steeringForce / agent->getMass();
	Vector2D velocity = agent->getVelocity() + acceleration * dtime;
	velocity = Vector2D::Truncate(velocity, agent->getMaxVelocity());

	agent->setVelocity(velocity);
	agent->setPosition(agent->getPosition() + velocity * dtime);
}

Vector2D Composite::calculateSteeringForce(Agent * agent)
{
	Vector2D steeringForce = Vector2D(0,0);

	for each (SteeringBehavior* steeringBehavior in *steeringBehaviors)
	{
		steeringForce += steeringBehavior->calculateSteeringForce(agent);
	}

	return steeringForce * priorityWeight;
}