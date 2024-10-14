#include "display.h"

void setUpWindow(Displayer* d) {
	SDL_Init(SDL_INIT_EVERYTHING);
	d->window = SDL_CreateWindow("SPACEJUNK", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
								SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	d->surface = SDL_GetWindowSurface(d->window);
	SDL_SetSurfaceBlendMode(d->surface, SDL_BLENDMODE_ADD);
}

void displayOnWindow(Displayer* d, Player* p) {
	SDL_Surface* wall = SDL_LoadBMP("images/wall.bmp"); // Load all the textures.
	SDL_Surface* wallL = SDL_LoadBMP("images/wall_L.bmp");
	SDL_Surface* wallR = SDL_LoadBMP("images/wall_R.bmp");
	SDL_Surface* wallLR = SDL_LoadBMP("images/wall_LR.bmp");
	SDL_Surface* wallF = SDL_LoadBMP("images/wall_F.bmp");
	SDL_Surface* door = SDL_LoadBMP("images/door.bmp");
	SDL_Surface* doorL = SDL_LoadBMP("images/door_L.bmp");
	SDL_Surface* doorR = SDL_LoadBMP("images/door_R.bmp");
	SDL_Surface* doorLR = SDL_LoadBMP("images/door_LR.bmp");
	SDL_Surface* doorF = SDL_LoadBMP("images/door_F.bmp");
	SDL_Surface* pathF = SDL_LoadBMP("images/path_F.bmp");
	SDL_Surface* pathLR = SDL_LoadBMP("images/path_LR.bmp");

	SDL_Rect middle, right; // Coordinates on the screen.
	middle.y = right.y = 0;
	middle.x = 150;
	right.x = 450;

	unsigned char xF, yF, xL, yL, xR, yR; // Coordinates in the map.
	xF = xL = xR = p->x;
	yF = yL = yR = p->y;

	switch (p->direction) { // Set them accordingly.
	case NORTH:
		--yF; --yL; --yR; --xL; ++xR; break;
	case SOUTH:
		++yF; ++yL; ++yR; ++xL; --xR; break;
	case WEST:
		--xF; --xL; --xR; ++yL; --yR; break;
	case EAST:
		++xF; ++xL; ++xR; --yL; ++yR; break;
	}

	Tile tC = p->location[playerPos(p)]; // Set up the tiles.
	Tile tF =0; // Initialize them to zero just in case there are holes in the outer walls.
	Tile tL =0;
	Tile tR =0;

	SDL_FillRect(d->surface, NULL, SDL_MapRGB(d->surface->format, 0, 0, 0)); // Clear the surface.

	// This part is a whole hell of switches, could probably make it all shorter.
	switch (getNibble(tC, p->direction)) { // Whole screen display.
	case W_WALL:
		SDL_BlitSurface(wall, NULL, d->surface, NULL);
		break;
	case W_DOOR:
		SDL_BlitSurface(door, NULL, d->surface, NULL);
		break;
	default:
		if(areXYValid(xF,yF)) tF = p->location[posFromXY(xF, yF)];

		switch (getNibble(tF, (p->direction+3)%4)) { // Left part of the screen display.
		case W_WALL:
			SDL_BlitSurface(wallL, NULL, d->surface, NULL);
			break;
		case W_DOOR:
			SDL_BlitSurface(doorL, NULL, d->surface, NULL);
			break;
		default:
			if (areXYValid(xL, yL)) tL = p->location[posFromXY(xL, yL)];
			switch (getNibble(tL, p->direction)) {
			case W_WALL:
				SDL_BlitSurface(wallLR, NULL, d->surface, NULL);
				break;
			case W_DOOR:
				SDL_BlitSurface(doorLR, NULL, d->surface, NULL);
				break;
			default:
				SDL_BlitSurface(pathLR, NULL, d->surface, NULL);
			}
			break;
		}

		switch (getNibble(tF, (p->direction+1)%4)) { // Right part of the screen display.
		case W_WALL:
			SDL_BlitSurface(wallR, NULL, d->surface, &right);
			break;
		case W_DOOR:
			SDL_BlitSurface(doorR, NULL, d->surface, &right);
			break;
		default:
			if (areXYValid(xF, yF)) tR = p->location[posFromXY(xR, yR)];
			switch (getNibble(tR, p->direction)) {
			case W_WALL:
				SDL_BlitSurface(wallLR, NULL, d->surface, &right);
				break;
			case W_DOOR:
				SDL_BlitSurface(doorLR, NULL, d->surface, &right);
				break;
			default:
				SDL_BlitSurface(pathLR, NULL, d->surface, &right);
			}
			break;
		}

		switch (getNibble(tF, p->direction)) { // Middle part of the screen display.
		case W_WALL:
			SDL_BlitSurface(wallF, NULL, d->surface, &middle);
			break;
		case W_DOOR:
			SDL_BlitSurface(doorF, NULL, d->surface, &middle);
			break;
		default:
			SDL_BlitSurface(pathF, NULL, d->surface, &middle);
		}
		break;

		break;
	}

	// addCoordinates(Displayer* d, Player* p); I need to figure out how to display text...

	SDL_UpdateWindowSurface(d->window); // Display the result on the screen once we're done.

	SDL_FreeSurface(wall); // Unload all the textures.
	SDL_FreeSurface(wallL);
	SDL_FreeSurface(wallR);
	SDL_FreeSurface(wallLR);
	SDL_FreeSurface(wallF);
	SDL_FreeSurface(door);
	SDL_FreeSurface(doorL);
	SDL_FreeSurface(doorR);
	SDL_FreeSurface(doorLR);
	SDL_FreeSurface(doorF);
	SDL_FreeSurface(pathLR);
	SDL_FreeSurface(pathF);
}

void addCoordinates(Displayer* d, Player* p) {
	// WORK IN PROGRESS
}