#ifndef READDATABASE_HPP
#define READDATABASE_HPP
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string.h>
#include <fstream>
#include <queue>
#include <set>
#include <chrono>

using namespace std;

void readFileD();
void printHashItens();
void printHashClasses();

void readFileT();
void printFileT();
void saveCommonItens();
void printCommonItens();

void parametersCombination();
void combination(vector<string> v, int perm[], int index, int n, int permutedStringLength);
void printCombinations();

void intersectionsBetweenCombinations();
void computeClassIntersection(vector<int> intersections);
void classWithGreaterOverlap();

void stop();

void setFlowers();
void clearCache();
void clearCombinations();

#endif
