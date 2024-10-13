#include <stdio.h>
#include "SDL.h"
#include "dungeon.h"
#include "dataRead.h"
#include "display.h"

void gameDisplayLoop(Player* p, Displayer* d);
void handleKeyPress(SDL_Keycode k, Player* p);

int main() {

	Player p;
	p.direction = NORTH;
	p.maxHealth = 50;
	p.health = 50;
	p.keys = 0;
	p.chests = 0;
	p.location = 0;

	Floor dungeon[5];
	readMap(dungeon[0], "floor1.flr");

	for (int i = 0; i < FLOOR_SIZE; ++i) {
		if (!(i % FLOOR_WIDTH) && i) printf("\n");
		printf("%08X ", dungeon[0][i]);
	}

	playMap(&p, dungeon, 0);

	Displayer display;
	setUpWindow(&display);

	printf("\nX : %d\nY : %d\nD : %d\n", p.x, p.y, p.direction);

	gameDisplayLoop(&p, &display);

	printf("\nX : %d\nY : %d\nD : %d\n", p.x, p.y, p.direction);

	return 0;
}

void gameDisplayLoop(Player* p, Displayer* d) {
	char isPlaying = 1, isKeyDown = 0;

	while (isPlaying) {
		SDL_Event e;

		while (SDL_PollEvent(&e) != 0) {
			switch (e.type) {
			case SDL_KEYDOWN:
				if (!isKeyDown) {
					isKeyDown = 1;
					handleKeyPress(e.key.keysym.sym, p);
				}
				break;
			case SDL_KEYUP:
				isKeyDown = 0;
				break;
			case SDL_QUIT:
				isPlaying = 0;
				break;
			}

			displayOnWindow(d, p);
		}
	}
}

void handleKeyPress(SDL_Keycode k, Player* p) {
	switch (k) {
	case SDLK_UP:
		goForward(p);
		break;
	case SDLK_DOWN:
		goBackwards(p);
		break;
	case SDLK_LEFT:
		turn(p, 3);
		break;
	case SDLK_RIGHT:
		turn(p, 1);
		break;
	}
}