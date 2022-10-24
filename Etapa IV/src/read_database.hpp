#ifndef READDATABASE_HPP
#define READDATABASE_HPP
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include <vector>
#include <string.h>
#include <fstream>
#include <queue>
#include <algorithm>
#include <set>

using namespace std;

void readFileD();
void printHashItens();
void printHashClasses();

void readFileT();
void printFileT();
void saveCommonItens();
void printCommonItens();

void parametersCombination();
void combination(ofstream *file, vector<string> v, int perm[], int index, int n, int permutedStringLength);

void intersectionsBetweenCombinations();
void computeClassIntersection(vector<int> intersections);
void classWithGreaterOverlap();

void stop();

#endif