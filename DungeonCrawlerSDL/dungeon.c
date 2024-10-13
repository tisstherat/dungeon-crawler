#include "dungeon.h"

char getNibble(Tile tile, char nibble) {
	nibble %= sizeof(Tile) * 2; // make sure the nibble isn't out of the tile
	return (tile >> (4 * nibble)) & 0x0f; // complicated binary math
}

char getBit(unsigned short flags, char bit) {
	bit %= sizeof(unsigned short) * 8; // same as above but bit
	return (flags >> (bit)) & 0b1; // same complicated binary math
}

void setBit(unsigned short* flags, char bit, char value) {
	bit %= sizeof(unsigned short) * 8; // again and again I want a valid bit
	*flags &= ~(0b1 << (bit)); // remove ONE specific bit
	*flags += (value & 0b1) << (bit); // set it to the right bit
}

Wall getWall(Tile tile, Cardinal cardinal) { return getNibble(tile, cardinal);  }

void setWall(Tile* tile, Cardinal cardinal, Wall wall) {
	cardinal %= sizeof(Tile) * 2; // did you know that this line of code makes sure the nibble isn't out of the tile
	*tile &= ~(0x0f << (cardinal * 4)); // erase current wall using a bit mask
	*tile += (wall & 0x0f) << (cardinal * 4); // set the wall to the new one 
}

int posFromXY(unsigned int x, unsigned int y) {
	return x + y * FLOOR_WIDTH;
}

int playerPos(Player* player) {
	return posFromXY(player->x, player->y);
}

void playMap(Player* player, Dungeon dungeon, unsigned short position) {
	player->location = dungeon[position];
	player->position = position;
	player->keys = 0;	// Those are flag reristers, however they are stored in one single variable...
	player->chests = 0;	// Which means you can reset them bu just setting them to 0.
	for (int i = 0; i < FLOOR_SIZE; ++i) if
		(getNibble(player->location[i], STAIRS) == FLOOR_ENTRANCE) {
			player->x = i % FLOOR_WIDTH;
			player->y = i / FLOOR_WIDTH;
			return;
		}
	player->x = 0;
	player->y = 0;
}

void goForward(Player* player) {
	Tile t = player->location[playerPos(player)];
	switch (getWall(t, player->direction)) {
	case W_WALL:
		return;
	case W_DOOR:
		if (getNibble(t, KEY) && !getBit(player->keys, getNibble(t, KEY) - 1)) // The key nibble is to 0 if there is no key needed...
			return;															   // so the first key (0th) opens door with KEY = 1, et caetera.
	}

	switch (player->direction) {
	case NORTH:
		--player->y;
		break;
	case EAST:
		++player->x;
		break;
	case SOUTH:
		++player->y;
		break;
	case WEST:
		--player->x;
	}

	checkChest(player);

}

void goBackwards(Player* player) {
	turn(player, 2);
	goForward(player);
	turn(player, 2);
}

void turn(Player* player, char direction) {
	player->direction = (char)((unsigned char)(player->direction + direction) % 4);
}

void checkChest(Player* player) {
	Tile t = player->location[playerPos(player)];
	if (getNibble(t, CHEST_ID) == KEY_CHEST && !getBit(player->keys, getNibble(t, KEY) - 1)) { // Chests with the value 0xF contains a key

		setBit(&player->keys, getNibble(t, CHEST_CONTENT), 1);

	} else
	if (getNibble(t, CHEST_ID) && !getBit(player->chests, getNibble(t, CHEST_ID) - 1)) { // See goForward function.

		setBit(&player->chests, getNibble(t, CHEST_ID) - 1, 1); // Again and for the same reason as above, there is a -1.

		// TO DO :
		// AJOUTER LE STOCKAGE DES ITEMS

		player->health += 1;

	}
}