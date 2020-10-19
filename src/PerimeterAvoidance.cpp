#include "PerimeterAvoidance.h"
#include "Seek.h"

PerimeterAvoidance::PerimeterAvoidance(float _priorityWeight) : SteeringBehavior(_priorityWeight)
{
}

PerimeterAvoidance::~PerimeterAvoidance()
{
}

void PerimeterAvoidance::applySteeringForce(Agent *agent, float dtime)
{
	Vector2D steeringForce = calculateSteeringForce(agent);

	Vector2D acceleration = steeringForce / agent->getMass();
	Vector2D velocity = agent->getVelocity() + acceleration * dtime;
	velocity = Vector2D::Truncate(velocity, agent->getMaxVelocity());

	agent->setVelocity(velocity);
	agent->setPosition(agent->getPosition() + velocity * dtime);
}

Vector2D PerimeterAvoidance::calculateSteeringForce(Agent * agent)
{
	Vector2D desiredVelocity, steeringForce = Vector2D(0, 0);

	if (agent->getPosition().x < PERIMETER_BORDER)
		desiredVelocity.x = agent->getSpeed();
	else if (agent->getPosition().x > winSize.x - PERIMETER_BORDER)
		desiredVelocity.x = -agent->getSpeed();

	if (agent->getPosition().y < PERIMETER_BORDER)
		desiredVelocity.y = agent->getSpeed();
	else if (agent->getPosition().y > winSize.y - PERIMETER_BORDER)
		desiredVelocity.y = -agent->getSpeed();

	if (desiredVelocity.Length() > 0.0f) {

		steeringForce = desiredVelocity - agent->getVelocity();
		steeringForce /= agent->getSpeed();
		steeringForce *= agent->getMaxForce();
	}

	return steeringForce * this->K_PRIORITY_PERIMETER_AVOIDANCE;
}