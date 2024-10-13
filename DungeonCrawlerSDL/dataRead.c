#include "dataRead.h"

void readMap(Floor floor, const char* fileName) {

	FILE* file = fopen(fileName, "r");

	for (int i = 0; i < FLOOR_SIZE; ++i) {
		if (feof(file)) floor[i] = 0;
		else fscanf(file, "%x", floor + i);
	}

	fclose(file);

}