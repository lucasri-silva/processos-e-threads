#ifndef NEWDATA_HPP
#define NEWDATA_HPP
#include "primary_memory.hpp"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string.h>
#include <fstream>
#include <queue>
#include <set>
#include <chrono>

using namespace std;

typedef struct Classes Classes;

struct Classes {
    unsigned int irisVersicolor = 0;
    unsigned int irisVirginica = 0;
    unsigned int irisSetosa = 0;
};

void readFileT(queue<vector<string>> *itensT, int numberOfColumns);
void printFileT(queue<vector<string>> *itensT);
void saveCommonItens(vector<vector<string>> *commonItens, queue<vector<string>> *itensT, unordered_map<string, vector<int>> *itensD);
void printCommonItens(vector<vector<string>> *commonItens);

void parametersCombination(vector<vector<string>> *combinations, vector<vector<string>> *commonItens);
void combination(vector<vector<string>> *combinations, vector<string> v, int perm[], int index, int n, int permutedStringLength);
void printCombinations(vector<vector<string>> *combinations);

void intersectionsBetweenCombinations(vector<vector<string>> *combinations, int numberOfColumns, unordered_map<string, vector<int>> *itensD, unordered_map<string, vector<int>> *classesD, unordered_map<string, vector<int>> *cache, Classes *classes, int *cacheAccess);
void computeClassIntersection(vector<int> intersections, unordered_map<string, vector<int>> *classesD, Classes *classes);
void classWithGreaterOverlap(Classes *classes);

bool verifyTimeExecProcess(chrono::_V2::system_clock::time_point start, chrono::_V2::system_clock::time_point stop, string task, int priority);
void stop();
void clearClasses(Classes *classes);

#endif