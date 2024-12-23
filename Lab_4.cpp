﻿#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>

#include "Key.h"
#include "SBlock.h"

#define TOGGLE_BIT 0
#define WEAK_KEY 1
using namespace std;

struct HalfBlocks {
    int left;
    int right;
};
union Block64 {
    long long int a;
    char s[8];
    HalfBlocks half;
};

int PermutationTable[64] = {  // таблица 1
    57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7,
    56, 48, 40, 32, 24, 16, 8, 0, 58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4, 62, 54, 46, 38, 30, 22, 14, 6,
};

int tableE[48] = {            // таблица 3
    31, 0, 1, 2, 3, 4, 3, 4, 5, 6, 7, 8,
    7, 8, 9, 10, 11, 12, 11, 12, 13, 14, 15, 16,
    15, 16, 17, 18, 19, 20, 19, 20, 21, 22, 23, 24,
    23, 24, 25, 26, 27, 28, 27, 28, 29, 30, 31, 0
};


vector<Block64> getBlocks(string s) {
    string str = s;
    int startSubstr = 0;
    Block64 field;
    vector<Block64> vec;
    if (str.size() % 8 != 0) {
        int a = 8 - str.size() % 8;
        while (a > 0) {
            str.append(" ");
            a--;
        }
    }
    while (startSubstr < str.size()) {
        for (int i = 0; i < 8; i++) {
            field.s[i] = str[startSubstr + i];
        }
        startSubstr += 8;
        vec.push_back(field);
    }
    return vec;
}

string getString(vector<Block64> blocks) {
    string str;
    for (auto block : blocks) {
        for (int i = 0; i < 8; i++) {
            str += block.s[i];
        }
    }
    return str;
}

vector<Block64> initialPermutation(vector<Block64> inBlocks) {
    Block64 newBlock;
    vector<Block64> outBlocks;
    for (auto block : inBlocks) {
        newBlock.a = 0;
        for (int i = 0; i < 64; i++) {
            if ((1i64 << (PermutationTable[i])) & block.a) {
                newBlock.a |= (1i64 << i);
            }
            else {
                //newBlock.a &= ~(1 << i);
            }
        }
        outBlocks.push_back(newBlock);
    }
    return outBlocks;
}
vector<Block64>reversePermutatition(vector<Block64>& inBlocks) {
    Block64 newBlock;
    vector<Block64> outBlocks;
    for (auto block : inBlocks) {
        newBlock.a = 0;
        for (int i = 0; i < 64; i++) {
            if ((1i64 << i) & block.a) {
                newBlock.a |= (1i64 << (PermutationTable[i]));
            }
            else {
                //newBlock.a &= ~(1 << i);
            }
        }
        outBlocks.push_back(newBlock);
    }
    return outBlocks;
}

unsigned int function(int right, Key48 key) {
    Key48 expansion;
    expansion.k = 0;
    
    for (int i = 0; i < 48; i++) {
        if ((1i64 << (tableE[i])) & right) {
            expansion.k |= (1i64 << i);
        }
        else {
            //expansion.k &= ~(1 << i);
        }
    }
    expansion.k ^= key.k;
    return getHalfBlock(expansion);
}

vector<Block64> coding(vector<Block64>inBlocks, vector<Key48>keys) {
    Block64 newBlock;
    vector<Block64> outBlocks;
    int right;
    for (auto block : inBlocks) {
        newBlock = block;
        for (int i = 0; i < 16; i++) {
            //left = block.half.left;
            right = newBlock.half.right;
            newBlock.half.right = newBlock.half.left ^ function(right, keys[i]);
            newBlock.half.left = right;
        }
        int a = newBlock.half.left;
        newBlock.half.left = newBlock.half.right;
        newBlock.half.right = a;
        outBlocks.push_back(newBlock);
    }
    return outBlocks;
}

vector<Block64> decoding(vector<Block64>inBlocks, vector<Key48>keys) {
    Block64 newBlock;
    vector<Block64> outBlocks;
    int right;
    for (auto block : inBlocks) {
        newBlock = block;
        for (int i = 15; i >= 0; i--) {
            //left = block.half.left;
            right = newBlock.half.right;
            newBlock.half.right = newBlock.half.left ^ function(right, keys[i]);
            newBlock.half.left = right;
        }
        int a = newBlock.half.left;
        newBlock.half.left = newBlock.half.right;
        newBlock.half.right = a;
        outBlocks.push_back(newBlock);
    }
    return outBlocks;
}

string str;
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << "Введите строку:\n";
    //getline(cin, str);
    str = "abcdefgh";
    cout << str << endl;
    vector<Key48> keys;
#if WEAK_KEY
    //  0x0101010101010101
    //  0xfefefefefefefefe
    //  0x1f1f1f1f0e0e0e0e
    //  0xe0e0e0e0f1f1f1f1
    keys = getKeys(0x0101010101010101);
#else
    keys = getKeys(0x25df32ac2473dea2);
#endif
    vector<Block64> blocks = getBlocks(str);
    
    blocks = initialPermutation(blocks);
    blocks = coding(blocks, keys);
    //blocks = decoding(blocks, keys);
    blocks = reversePermutatition(blocks);
    str=getString(blocks);
    cout << str << endl << endl;

#if TOGGLE_BIT
    // инвертирование 20 бита 0 блока
    if (blocks[0].a & (1<< 20)) {
        blocks[0].a &= ~(1 << 20);
    }
    else {
        blocks[0].a |= (1 << 20);
    }
#endif

    blocks = initialPermutation(blocks);
#if WEAK_KEY
    blocks = coding(blocks, keys);
#else
    blocks = decoding(blocks, keys);
#endif    
    blocks = reversePermutatition(blocks);
    str = getString(blocks);
    cout << str << endl;
    return 0;
}
