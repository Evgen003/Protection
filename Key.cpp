#include "Key.h"

int tablePC1[56] = {        // таблица 6
    56, 48, 40, 32, 24, 16, 8, 0, 57, 49, 41, 33, 25, 17,
    9, 1, 58, 50, 42, 34, 26, 18, 10, 2, 59, 51, 43, 35,
    62, 54, 46, 38, 30, 22, 14, 6, 61, 53, 45, 37, 29, 21,
    13, 5, 60, 52, 44, 36, 28, 20, 12, 4, 27, 19, 11, 3
};
int shiftsTable[16] = {          // таблица 7
    1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};
int tablePC2[48] = {        // таблица 8
    13, 16, 10, 23, 0, 4, 2, 27, 14, 5, 20, 9, 22, 18, 11, 3,
    25, 7, 15, 6, 26, 19, 12, 1, 40, 51, 30, 36, 46, 54, 29, 39,
    50, 44, 32, 47, 43, 48, 38, 55, 33, 52, 45, 41, 49, 35, 28, 31
};

vector<Key48> getKeys(long long int inKey) {
    vector<Key48> keys48;
	Key56 key56;
    Half56 half56;
    key56.k = 0;
    
    for (int i = 0; i < 56; i++) {
        if ((1i64 << (tablePC1[i] + 1)) & inKey) {
            key56.k |= (1i64 << i);
        }
        else {
            //key56.k &= ~(1 << i);
        }
    }
    half56.left = key56.k >> 28;
    half56.right = key56.k;

    for (int i = 0; i < 16; i++) {
        int shifts = shiftsTable[i];
        while (shifts > 0) {
            shifts--;
            half56.left = (half56.left << 1) | (half56.left >> (28 - 1));
            half56.right = (half56.right << 1) | (half56.right >> (28 - 1));
        }
        Key56 conc;
        conc.k = (half56.left << 28) | half56.right;
        Key48 key48;
        key48.k = 0;
        for (int j = 0; j < 48; j++) {
            if ((1i64 << (tablePC2[j])) & conc.k) {
                key48.k |= (1i64 << j);
            }
            else {
                //key48.k &= ~(1 << j);
            }
        }
        keys48.push_back(key48);
    }
    return keys48;
} 