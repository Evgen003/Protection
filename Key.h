#pragma once
#include <vector>
#include <iostream>
using namespace std;
// объединение для 64 битного ключа
union Key64 {
    unsigned long long int k;
    char blocks[8];
};
// структура для 56 битного ключа
struct Key56 {
    unsigned long long int k : 56;
};
// структура для 28 битных векторов
struct Half56 {
    unsigned int right : 28;
    unsigned int left : 28;
};
// структура для 48 битного ключа
struct Key48 {
    unsigned long long int k : 48;
};
extern int tablePC1[56];
extern int shiftsTable[16];
extern int tablePC2[48];
// функция формирующая ключи
vector<Key48> getKeys(long long int key);
