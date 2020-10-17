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

Vector2D Seek::obstacleAvoidanceForce(Agent* agent, std::vector<Obstacle>* obstacles)
{
	Vector2D raycastVector = agent->getPosition();
	raycastVector += agent->getVelocity().Normalize() * avoidanceLookahead;
	bool obstacleAvoidanceCollision = false;

	Vector2D auxCollisionPoint, collisionPoint = NULL;
	Vector2D normalVector;

	for each (Obstacle obs in *obstacles)
	{
		for (int i = 0; i < 4; ++i)
		{
			if (Vector2DUtils::SegmentSegmentIntersection(obs.vertices[i], obs.vertices[(i + 1 == 5) ? 0 : i], agent->getPosition(), raycastVector, obstacleAvoidanceCollision, &auxCollisionPoint))
			{
				if (collisionPoint == NULL || collisionPoint.Length() > auxCollisionPoint.Length())
				{
					normalVector = obs.normals[i];
					collisionPoint = auxCollisionPoint;
				}
			}
		}
	}

	if (collisionPoint != NULL) {
		Vector2D avoidTarget = collisionPoint;
		avoidTarget += normalVector * avoidanceLookahead;
		return calculateSeekForce(avoidTarget, agent);
	}
	return Vector2D(0, 0);
}