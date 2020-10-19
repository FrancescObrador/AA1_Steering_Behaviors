#pragma once
#include <iostream>
#include <minmax.h>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_SimpleApp.h"
#include <vector>
#include "Vector2D.h"
#include "utils.h"
#include "Obstacle.h"


class Agent
{
public:
	class SteeringBehavior
	{
	protected:
		Vector2D winSize;
		float avoidanceLookahead = 100;
		float priorityWeight = 1;
	public:
		SteeringBehavior(float _priorityWeight) {
			winSize = Vector2D(1280, 768);
			priorityWeight = _priorityWeight;
		};

		virtual ~SteeringBehavior() {};
		virtual void applySteeringForce(Agent *agent, float dtime) {};
		virtual Vector2D calculateSteeringForce(Agent *agent) 
		{ 
			return Vector2D(0, 0); 
		};
	};

private:
	SteeringBehavior *steering_behaviour;
	Vector2D position;
	Vector2D velocity;
	Vector2D targetPosition;	//TODO si nos da tiempo ya si eso lo quitamos
	Agent* targetAgent;


	float mass;
	float speed;
	float orientation;
	float max_force;
	float max_velocity;

	SDL_Texture *sprite_texture;
	bool draw_sprite;
	int sprite_num_frames;
	int sprite_w;
	int sprite_h;

public:
	Agent();
	~Agent();
	Vector2D getPosition();
	Vector2D getTarget();
	Vector2D getVelocity();
	Agent* getTargetAgent();
	float getMass();
	float getMaxVelocity();
	float getMaxForce();
	float getSpeed();
	void setBehavior(SteeringBehavior *behavior);
	void setPosition(Vector2D position);
	void setTarget(Vector2D target);
	void setVelocity(Vector2D velocity);
	void setSpeed(float speed);
	void setTargetAgent(Agent *agent);
	void update(float dtime, SDL_Event *event);
	void draw();
	bool Agent::loadSpriteTexture(char* filename, int num_frames=1);
	
};
