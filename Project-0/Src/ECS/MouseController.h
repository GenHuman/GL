#pragma once
#pragma once
#include "../Game.h"
#include "Components.h"

class MouseController : public Component
{
public:
	TransformComponent *transform;
	Vector2D *target = nullptr;
	bool rbmStillDown = false;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override
	{

		if (Game::event.type == SDL_MOUSEBUTTONDOWN)
		{
			switch (Game::event.button.button)
			{
			case SDL_BUTTON_RIGHT:
				target = new Vector2D((float)Game::event.button.x, (float)Game::event.button.y);
				rbmStillDown = true;

				//std::cout << *target << std::endl;
				//std::cout << Game::event.button.x << " - "<< Game::event.button.y << std::endl;
				/*if (transform->position.x > Game::event.button.x) {
					transform->velocity.x = -1;
				}else if (transform->position.x < Game::event.button.x) {
					transform->velocity.x = 1;
				}
				if (transform->position.y > Game::event.button.y) {
					transform->velocity.y= -1;
				}else if (transform->position.y > Game::event.button.y) {
					transform->velocity.y = 1;
				}*/
				break;

			default:
				break;
			}
		}

		if (Game::event.type == SDL_MOUSEBUTTONUP)
		{
			switch (Game::event.button.button)
			{
			case SDL_BUTTON_RIGHT:
				rbmStillDown = false;
				break;

			default:
				break;
			}
		}

		if (Game::event.type == SDL_MOUSEMOTION &&rbmStillDown)
		{
			target = new Vector2D((float)Game::event.button.x, (float)Game::event.button.y);
		}

		if (target) {
			if (target->x != transform->position.x || target->y != transform->position.y)
			{
				if (transform->position.x > target->x) {
					transform->velocity.x = -1;
				}
				else if (transform->position.x < target->x) {
					transform->velocity.x = 1;
				}
				if (transform->position.y > target->y) {
					transform->velocity.y = -1;
				}
				else if (transform->position.y < target->y) {
					transform->velocity.y = 1;
				}
			}
			else {
				target = nullptr;
				transform->velocity.y = 0;
				transform->velocity.x = 0;
			}
		}
	}

};