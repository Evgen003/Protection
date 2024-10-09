#pragma once
#include "Key.h"

using namespace std;

struct SBlock {
	unsigned char s1 : 6;
	//unsigned char s2 : 6;
	//unsigned char s3 : 6;
	//unsigned char s4 : 6;
	//unsigned char s5 : 6;
	//unsigned char s6 : 6;
	//unsigned char s7 : 6;
	//unsigned char s8 : 6;
};
extern int TableSBlocks[8][4][16];
int getHalfBlock(Key48);