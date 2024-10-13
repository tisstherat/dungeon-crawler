#ifndef __DUNGEON__
#define __DUNGEON__

/*
* Miscellaneous consts.
*/
enum {FLOOR_SIZE = 100, FLOOR_WIDTH = 10, FLOOR_ENTRANCE = 1, FLOOR_EXIT, KEY_CHEST = 15};

/*
* Cardinal consts.
*/
typedef enum {NORTH, EAST, SOUTH, WEST, CHEST_CONTENT, CHEST_ID, KEY, STAIRS} Cardinal;

/*
* Wall consts.
*/
typedef enum {W_NONE, W_FAKEWALL, W_DOOR, W_WALL} Wall;

/*
* IDs of each game item.
*/
typedef enum {} Item;

/*
* Tile is a 4-byte var representing a dungeon tile.
* It is cut down in 8 nibbles (4 bits) each representing specific value :
* (It can be represented in HEX value (e.g. 0x0013F41A) where each character represents a nibble.)
* 
* n : 7______6______5______4_______3_____2______1_____0
* [STAIRS][ KEY ][ __ CHEST __ ][ ________ WALLS _______ ]
* _______________[ ID ][CONTENT][WEST][SOUTH][EAST][NORTH]
* 
* - WALLS are each wall of the room represented as a value (see enum Wall).
* - CHEST CONTENT refers to the item stored inside the chest on the tile (0 of no chest).
* - CHEST ID is used to make sure you can only open a chest once (works like KEY below).
* - KEY is the key that locks the door (useless if the wall isn't a door).
* - STAIRS indicates the beginning and the end of a level.
*/
typedef int Tile;

/*
* Floor is an array of Tiles that represents a 10 by 10 dungeon floor.
*/
typedef Tile Floor[FLOOR_SIZE];

/*
* Dungeon represents the whole dungeon as it is an array of floors.
*/
typedef Floor* Dungeon;

/*
* Represents the player and its data.
* @health : the current health of the player.
* @maxHealth : the maximum health of the player.
* @x : the X coordinate of the player.
* @y : the Y coordinate of the player.
* @direction : the cardinal direction of the player (N/E/S/W).
* @keys : flags register that stores which keys you have.
* @chest : flags register that stores which chests you have opened.
* @position : the floor of the dungeon where the player is.
* @location : the floor where the player currently is.
*/
typedef struct {
	unsigned short health, maxHealth;
	unsigned char x, y;
	Cardinal direction;
	unsigned short keys;
	unsigned short chests;
	unsigned short position;
	Tile* location;
}Player;

/*
* Returns Nth nibble from the tile parameter.
* @tile : the Tile to extract the nibble from.
* @nibble : the index of the nibble (modulo 8).
*/
char getNibble(Tile tile, char nibble);

/*
* Returns Nth bit from the flags parameter.
* @flags : the var to extract the bit from.
* @bit : the index of the bit.
*/
char getBit(unsigned short flags, char bit);

/*
* Returns Nth bit from the flags parameter.
* @flags : pointer to the var to change the bit.
* @bit : the index of the bit.
* @value : the value of the bit (modulo 2).
*/
void setBit(unsigned int* flags, char bit, char value);

/*
* Does the same as getNibble().
*/
Wall getWall(Tile tile, Cardinal cardinal);

/*
* Sets a wall of a tile to a certain wall type (I don't even plan to use it).
* @tile : pointer to the Tile that gets modified.
* @cardinal : the wall that will be changed.
* @wall : the type of the new wall.
*/
void setWall(Tile* tile, Cardinal cardinal, Wall wall);

/*
* Returns the index where the Player "is" in his location array.
* @player : a pointer to the player.
*/
int playerPos(Player* player);

/*
* Places the player on the floor at its starting point (0:0 if there is no starting point).
* @Player : a pointer to the Player.
* @The map to put the player on.
*/
void playMap(Player* player, Dungeon dungeon, unsigned short position);

/*
* Makes the player go forward if possible.
* @Player : a pointer to the Player.
*/
void goForward(Player* player);

/*
* Makes the player go backwards if possibe.
* @Player : a pointer to the Player.
*/
void goBackwards(Player* player);

/*
* Makes the player turn right N times (use a negative value or 3 to go left).
* @Player : a pointer to the Player.
* @direction : the amount of times the player turns right.
*/
void turn(Player* player, char direction);

/*
* Checks if a chest is on the player's Tile and opens it.
* The chest content can either be a key or an item.
* @player : a pointer to the Player.
*/
void checkChest(Player* player);

#endif