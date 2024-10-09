#pragma once
#include <vector>
#include <iostream>
using namespace std;

union Key64 {
    unsigned long long int k;
    char blocks[8];
};
struct Key56 {
    unsigned long long int k : 56;
};
struct Half56 {
    unsigned int left : 28;
    unsigned int right : 28;
};
struct Key48 {
    unsigned long long int k : 48;
};
extern int tablePC1[56];
extern int shiftsTable[16];
extern int tablePC2[48];

vector<Key48> getKeys(long long int key);