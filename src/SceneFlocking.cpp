#include "SceneFlocking.h"
#include "Seek.h"
#include "ObstacleAvoidance.h"
#include "Pursue.h"
#include "Composite.h"
#include "PerimeterAvoidance.h"

using namespace std;

SceneFlocking::SceneFlocking(int agentsNum)
{
	flockingAgents = new std::vector<Agent*>();
	obstacles = new std::vector<Obstacle>();
	
	obstacles->push_back(Obstacle(Vector2D(200, 200), Vector2D(300, 75)));
	obstacles->push_back(Obstacle(Vector2D(200, 450), Vector2D(300, 75)));
	
	obstacles->push_back(Obstacle(Vector2D(600, 150), Vector2D(100, 450)));

	obstacles->push_back(Obstacle(Vector2D(900, 325), Vector2D(150, 150)));
	
	obstacles->push_back(Obstacle(Vector2D(975, 125), Vector2D(50, 125)));
	obstacles->push_back(Obstacle(Vector2D(975, 550), Vector2D(50, 125)));

	std::vector<Agent::SteeringBehavior*>* sBEnemyList = new std::vector<Agent::SteeringBehavior*>();
	sBEnemyList->push_back(new Flocking(flockingAgents, 2));
	sBEnemyList->push_back(new Pursue(10));
	sBEnemyList->push_back(new ObstacleAvoidance(obstacles, 125));
	sBEnemyList->push_back(new PerimeterAvoidance(150));


	Agent* agent;
	for (int i = 0; i < agentsNum; i++)
	{
		agent = new Agent;
		agent->setBehavior(new Composite(sBEnemyList, 1));
		agent->setTarget(Vector2D(100, 100));
		agent->setPosition(Vector2D(100, 100 + i*10));
		agent->loadSpriteTexture("../res/zombie1.png", 8);
		agent->setSpeed(10);
		agents.push_back(agent);
		flockingAgents->push_back(agent);
	}

	agent = new Agent();

	std::vector<Agent::SteeringBehavior*>* sBList = new std::vector<Agent::SteeringBehavior*>();
	sBList->push_back(new Seek(1));
	sBList->push_back(new ObstacleAvoidance(obstacles, 100));

	agent->setBehavior(new Composite(sBList, 1));
	agent->setSpeed(0.25f);
	agent->setPosition(Vector2D(550, 150));
	agent->setTarget(Vector2D(900, 650));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	
	int count = 0;
	for each (Agent* flockingAgent in *flockingAgents)
	{
		flockingAgent->setTargetAgent(agent);
	}

	agents.push_back(agent);
	target = Vector2D(100, 100);

}

SceneFlocking::~SceneFlocking()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneFlocking::update(float dtime, SDL_Event* event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			target = Vector2D((float)(event->button.x), (float)(event->button.y));
			agents[agents.size()-1]->setTarget(target);
		}
		break;
	default:
		break;
	}

	for (int i = 0; i < (int)agents.size(); i++)
	{
		agents[i]->update(dtime, event);
	}

}

void SceneFlocking::draw()
{
	for each (Obstacle obs in *obstacles)
	{
		drawBox(TheApp::Instance()->getRenderer(), obs.vertices[0], obs.size, 50, 235, 230, 255);
	}

	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	for (int i = 0; i < (int)agents.size(); i++)
	{
		agents[i]->draw();
	}
}

const char* SceneFlocking::getTitle()
{
	return "SDL Steering Behaviors :: Flocking Demo";
}