#include "SceneFlocking.h"
#include "Seek.h"
using namespace std;

SceneFlocking::SceneFlocking()
{
	flockingAgents = new std::vector<Agent*>();
	obstacles = new std::vector<Obstacle>();

	//int countBoxes = 2;
	//int paddingX = (1280 - 400) / (countBoxes*2);
	//int paddingY = (768 - 400) / (countBoxes*2);
	//for (int i = 0; i < countBoxes; ++i)
	//{
	//	for (int j = 0; j < countBoxes; ++j)
	//	{//if(i%2 == 0)
	//		obstacles->push_back(Obstacle(Vector2D((paddingX * i *2) + 200, (paddingY * j * 2) + 200), Vector2D(paddingX, paddingY)));
	//	}
	//}
	
	obstacles->push_back(Obstacle(Vector2D(200, 200), Vector2D(300, 75)));
	obstacles->push_back(Obstacle(Vector2D(200, 450), Vector2D(300, 75)));
	
	obstacles->push_back(Obstacle(Vector2D(600, 150), Vector2D(100, 450)));

	obstacles->push_back(Obstacle(Vector2D(900, 325), Vector2D(150, 150)));
	
	obstacles->push_back(Obstacle(Vector2D(975, 125), Vector2D(50, 125)));
	obstacles->push_back(Obstacle(Vector2D(975, 550), Vector2D(50, 125)));

	


	Agent* agent;
	for (int i = 0; i < 500; i++)
	{
		 agent = new Agent;
		agent->setBehavior(new Flocking(flockingAgents, obstacles));
		agent->setTarget(Vector2D(100, 100));
		agent->setPosition(Vector2D(100, 100 + i*10));
		agent->loadSpriteTexture("../res/zombie1.png", 8);
		agent->setSpeed(10);
		agents.push_back(agent);
		flockingAgents->push_back(agent);
	}

	agent = new Agent();
	agent->setBehavior(new Seek(obstacles));
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