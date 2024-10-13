#include "display.h"

void setUpWindow(Displayer* d) {
	SDL_Init(SDL_INIT_EVERYTHING);
	d->window = SDL_CreateWindow("SPACEJUNK", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
								SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	d->surface = SDL_GetWindowSurface(d->window);
}

void displayOnWindow(Displayer* d, Player* p) {
	SDL_Surface* wall = SDL_LoadBMP("images/wall.bmp");
	SDL_Surface* path = SDL_LoadBMP("images/path.bmp");
	SDL_Surface* door = SDL_LoadBMP("images/door.bmp");

	Tile t = p->location[playerPos(p)];

	switch (getNibble(t, p->direction))
	{
	case W_WALL:
		SDL_BlitSurface(wall, NULL, d->surface, NULL);
		break;
	case W_DOOR:
		SDL_BlitSurface(door, NULL, d->surface, NULL);
		break;
	default:
		SDL_BlitSurface(path, NULL, d->surface, NULL);
		break;
	}

	SDL_UpdateWindowSurface(d->window);

	SDL_FreeSurface(wall);
	SDL_FreeSurface(path);
	SDL_FreeSurface(door);
}