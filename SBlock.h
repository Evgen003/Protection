#pragma once
#include "Key.h"

using namespace std;
// структура для 6 битных S-блоков
struct SBlock {
	unsigned char s1 : 6;
};
extern int TableSBlocks[8][4][16];
int getHalfBlock(Key48);
