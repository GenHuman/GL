#pragma once
struct Animation
{
	int index;
	int frames;
	int msDelay;

	Animation(){}

	Animation(int i, int f, int s)
	{
		index = i;
		frames = f;
		msDelay = s;
	}

};