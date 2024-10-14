#ifndef __DUNGEONDISPLAY__
#define __DUNGEONDISPLAY__
#include "SDL.h"
#include "dungeon.h"

/*
* The dimentions of the window.
*/
enum {SCREEN_WIDTH = 600, SCREEN_HEIGHT = 400};

/*
* This struct is really for the display function calls to look cleaner.
* @window : a pointer to the SDL window used for screen display.
* @surface : a pointer to the SDL surface used for screen display.
*/
typedef struct {
	SDL_Window* window;
	SDL_Surface* surface;
}Displayer;

/*
* Sets up the window and initializes everything SDL-related.
* @displayer : the window and its surface.
*/
void setUpWindow(Displayer* displayer);

/*
* Displays what the player sees on the window.
* @displayer : the window and its surface.
* @player :	a pointer to the player.
*/
void displayOnWindow(Displayer* displayer, Player* player);

/*
* Add the coordinates in the coner of the window.
* @displayer : the window and its surface.
* @player :	a pointer to the player.
*/
void addCoordinates(Displayer* displayer, Player* player);

#endif