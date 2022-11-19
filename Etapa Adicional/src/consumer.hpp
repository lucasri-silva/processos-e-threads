#ifndef CONSUMER_HPP
#define CONSUMER_HPP
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <unordered_map>
#include <string>
#include <chrono>
#include <thread>
#include <string.h>
#include <mutex>

using namespace std;

void intersectionsBetweenCombinations(vector<string> *combinations, unordered_map<string, vector<int>> *itensD, unordered_map<string, vector<int>> *classesD, int *producer_on);
void computeClassIntersection(vector<int> intersections, unordered_map<string, vector<int>> classesD);
void classWithGreaterOverlap();
void printCombinations(vector<string> *combinations);

void clearCache();

void setCombinationsThreadIndex();
void setFlowers();


#endif