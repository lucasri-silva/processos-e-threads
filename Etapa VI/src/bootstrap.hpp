#ifndef BOOTSTRAP_HPP
#define BOOTSTRAP_HPP
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string.h>
#include <fstream>

using namespace std;

typedef struct Classes Classes;

void readFileD(unordered_map<string, vector<int>> *itensD, unordered_map<string, vector<int>> *classesD, int numberOfColumns);
void printHashItens(unordered_map<string, vector<int>> *itensD);
void printHashClasses(unordered_map<string, vector<int>> *classesD);

#endif