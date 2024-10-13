#ifndef __DATAREAD__
#define __DATAREAD__
#include <stdio.h>
#include "dungeon.h"
#pragma warning(disable : 4996)

/*
* Reads a file and puts it it into a Floor
* @floor : the Floor where the data is stored
* @fileName : the name of the file
*/
void readMap(Floor floor, const char* fileName);

#endif