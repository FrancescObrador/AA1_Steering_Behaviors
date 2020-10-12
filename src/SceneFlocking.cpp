#include "SceneFlocking.h"
#include "Seek.h"
using namespace std;

SceneFlocking::SceneFlocking()
{
	flockingAgents = new std::vector<Agent*>();

	Agent* agent;
	for (int i = 0; i < 10; i++)
	{
		 agent = new Agent;
		agent->setBehavior(new Flocking(flockingAgents));
		agent->setTarget(Vector2D(100, 100));
		agent->setPosition(Vector2D(20, 20 + i));
		agent->loadSpriteTexture("../res/zombie1.png", 8);
		agents.push_back(agent);
		flockingAgents->push_back(agent);
	}

	agent = new Agent();
	agent->setBehavior(new Seek);
	agent->setPosition(Vector2D(600, 50));
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
		}
		break;
	default:
		break;
	}
	target = agents[1]->getPosition();
	agents[0]->setTarget(target);
	for (int i = 0; i < (int)agents.size(); i++)
	{
		agents[i]->update(dtime, event);
	}

}

void SceneFlocking::draw()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		agents[i]->draw();
	}
}

const char* SceneFlocking::getTitle()
{
	return "SDL Steering Behaviors :: Flocking Demo";
}