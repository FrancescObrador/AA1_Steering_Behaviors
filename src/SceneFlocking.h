#pragma once
#include "Scene.h"
#include "Flocking.h"
#include "Obstacle.h"

class SceneFlocking :
	public Scene
{
public:
	SceneFlocking();
	~SceneFlocking();
	void update(float dtime, SDL_Event* event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	std::vector<Agent*>* flockingAgents;
	Vector2D target;

	std::vector<Obstacle>* obstacles;
};

