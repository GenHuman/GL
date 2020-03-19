#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"



Map *map;

Manager manager;


SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;


auto& player(manager.addEntity());
//auto& wall(manager.addEntity());

const char* mapfile = "Assets/terrain_ss.png";


enum groupLabels : std::size_t
{
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};

Game::Game()
{
}


Game::~Game()
{
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialized!..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Window created!" << std::endl;
		}


		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}

		isRunning = true;
	}
	else {
		isRunning = false;
	}

	map = new Map();


	Map::LoadMap("Assets/map.map",25, 20);




	player.addComponent<TransformComponent>(Vector2D(4, 4));
	player.addComponent<SpriteComponent>("Assets/enemy_anims.png", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	/*wall.addComponent<TransformComponent>(300.0f, 300.f, 300, 20, Vector2D(1, 1));
	wall.addComponent<SpriteComponent>("Assets/dirt.png");
	wall.addComponent<ColliderComponent>("wall");
	wall.addGroup(groupMap);*/

}

void Game::handleEvents()
{


	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}

}

void Game::update()
{


	manager.refresh();
	manager.update();

	for (auto cc : colliders)
	{
		if (Collision::AABB(player.getComponent<ColliderComponent>(), *cc))
		{
			//player.getComponent<TransformComponent>().velocity*-1;
			//std::cout << "ouch" << std::endl;
		}
	}
	//player.getComponent<TransformComponent>().position.Add(Vector2D(5,0));


	/*if (player.getComponent<TransformComponent>().position.x > 100)
	{
		player.getComponent<SpriteComponent>().setTex("Assets/enemy_idle.png");
	}*/

	//std::cout << player.getComponent<TransformComponent>().position << std::endl;

}

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));

void Game::render()
{
	SDL_RenderClear(renderer);
	for (auto& t : tiles)
	{
		t->draw();
	}
	for (auto& p:players)
	{
		p->draw();
	}
	for (auto& e : enemies)
	{
		e->draw();
	}
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	std::cout << "Game cleared!" << std::endl;
}

void Game::AddTile(int srcX, int srcY, int x, int y)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, x, y, mapfile);
	tile.addGroup(groupMap);
	//tile.addComponent<ColliderComponent>("grass");
}