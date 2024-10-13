#ifndef __DUNGEONDISPLAY__
#define __DUNGEONDISPLAY__
#include "SDL.h"
#include "dungeon.h"

enum {SCREEN_WIDTH = 600, SCREEN_HEIGHT = 400};

typedef struct {
	SDL_Window* window;
	SDL_Surface* surface;
}Displayer;

void setUpWindow(Displayer* d);

void displayOnWindow(Displayer* d, Player* p);

#endif