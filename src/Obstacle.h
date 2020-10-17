#pragma once
#include "Vector2D.h"

class Obstacle
{
public:
	Vector2D size;

	Vector2D vertices[4];
    Vector2D normals[4] = {Vector2D(0,-1), Vector2D(1, 0), Vector2D(0, 1), Vector2D(-1, 0)};

	Obstacle(Vector2D position, Vector2D _size) 
	{
		size = _size;
		vertices[0] = position;

		vertices[1].x = position.x + _size.x;
		vertices[1].y = position.y;

		vertices[2] = position + _size;
		
		vertices[3].x = position.x;
		vertices[3].y = position.y  + _size.y;
	}

};