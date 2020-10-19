#include "ObstacleAvoidance.h"
#include "Seek.h"

ObstacleAvoidance::ObstacleAvoidance(std::vector<Obstacle>* _obstacles, float _priorityWeight) : SteeringBehavior(_priorityWeight)
{
	obstacles = _obstacles;
}

ObstacleAvoidance::~ObstacleAvoidance()
{
}

void ObstacleAvoidance::applySteeringForce(Agent *agent, float dtime)
{
	Vector2D steeringForce = calculateSteeringForce(agent);

	Vector2D acceleration = steeringForce / agent->getMass();
	Vector2D velocity = agent->getVelocity() + acceleration * dtime;
	velocity = Vector2D::Truncate(velocity, agent->getMaxVelocity());

	agent->setVelocity(velocity);
	agent->setPosition(agent->getPosition() + velocity * dtime);
}

Vector2D ObstacleAvoidance::calculateSteeringForce(Agent * agent)
{
	Vector2D raycastVector = agent->getPosition();
	raycastVector += agent->getVelocity().Normalize() * avoidanceLookahead;
	bool obstacleAvoidanceCollision = false;

	Vector2D collisionPoint = NULL;
	Vector2D* auxCollisionPoint = new Vector2D(0, 0);
	Vector2D normalVector;

	for each (Obstacle obs in *obstacles)
	{
		for (int i = 0; i < 4; ++i)
		{
			if (Vector2DUtils::SegmentSegmentIntersection(obs.vertices[i], obs.vertices[(i + 1 == 4) ? 0 : i + 1], agent->getPosition(), raycastVector, auxCollisionPoint))
			{
				if (collisionPoint == NULL || collisionPoint.Length() > auxCollisionPoint->Length())
				{
					normalVector = obs.normals[i];
					collisionPoint = *auxCollisionPoint;
				}
			}
		}
	}

	if (collisionPoint != NULL) {
		Vector2D avoidTarget = collisionPoint;
		avoidTarget += normalVector * 10;
		Seek* auxSeek = new Seek(priorityWeight);

		Agent* fakeTarget = new Agent(*agent);
		fakeTarget->setTarget(avoidTarget);

		return auxSeek->calculateSteeringForce(fakeTarget);
	}
	return Vector2D(0, 0);
}