#pragma once
#include "Components.h"
#include "../Vector2D.h"

class TransformComponent : public Component
{


public:

	Vector2D position;
	Vector2D velocity;

	int height = 32; 
	int width = 32;
	Vector2D scale;

	int speed = 3;


	TransformComponent()
	{
		position.Zero();
		scale.x = 1;
		scale.y = 1;
	}

	TransformComponent(Vector2D v)
	{
		position.Zero();
		scale = v;
	}

	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y, int w, int h, Vector2D sc)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	void init() override
	{
		velocity.Zero();
	}

	void update() override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}


};