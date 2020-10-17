#include "Flocking.h"

Flocking::Flocking()
{

}

Flocking::Flocking(std::vector<Agent*>* _flockingAgents)
{
	flockingAgents = _flockingAgents;
}

Flocking::~Flocking()
{
}

void Flocking::applySteeringForce(Agent* agent, float dtime)
{
	Vector2D steeringForce = calculateFlockingForce(agent) + 
		calculatePursueForce(agent->getTargetAgent()->getPosition(), agent->getTargetAgent()->getVelocity(), agent) + 
		perimeterAvoidanceForce(agent);

	Vector2D acceleration = steeringForce / agent->getMass();
	Vector2D velocity = agent->getVelocity() + acceleration * dtime;
	velocity = Vector2D::Truncate(velocity, agent->getMaxVelocity());

	agent->setVelocity(velocity);
	agent->setPosition(agent->getPosition() + velocity * dtime);
}

Vector2D Flocking::calculateFlockingForce(Agent* agent)
{
	Vector2D separationVector = Vector2D(0,0);
	Vector2D averagePosition = Vector2D(0, 0);
	Vector2D averageVelocity = Vector2D(0, 0);

	int neighborCount = 0;

	for each (Agent *flockingAgent in *flockingAgents)
	{
		if (Vector2D::Distance(flockingAgent->getPosition(), agent->getPosition()) <= NEIGHBOR_RADIUS)
		{
			// Separation
			separationVector += (agent->getPosition() - flockingAgent->getPosition());

			// Cohesion
			averagePosition += agent->getPosition();

			//Alignment
			averageVelocity += agent->getVelocity();

			++neighborCount;
		}
	}

	// neighborCount should't be 0 because the agent couts himself
	separationVector /= neighborCount;
	averagePosition /= neighborCount;
	averagePosition -= agent->getPosition();
	averageVelocity /= neighborCount;

	Vector2D separationDirection = Vector2D::Normalize(separationVector);
	Vector2D cohesionDirection = Vector2D::Normalize(averagePosition);
	Vector2D alignmentDirection = Vector2D::Normalize(averageVelocity);

	return	separationDirection * K_SEPARATION_FORCE + 
			cohesionDirection * K_COHESION_FORCE + 
			alignmentDirection * K_ALIGNMENT_FORCE;

}
