#pragma once
#include "Key.h"

using namespace std;
// ��������� ��� 6 ������ S-������
struct SBlock {
	unsigned char s1 : 6;
};
extern int TableSBlocks[8][4][16];
int getHalfBlock(Key48);