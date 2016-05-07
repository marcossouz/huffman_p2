#include "bitop.h"

int setBit(int character, int position){
	int mask = 1 << position;
	return mask | character;
}

int isBitISet(int character, int position){
    int mask = 1 << position;
    return mask & character;
}
