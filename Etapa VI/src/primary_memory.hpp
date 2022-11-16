#ifndef PRIMARYMEMORY_HPP
#define PRIMARYMEMORY_HPP
#include "newdata.hpp"
#include <iostream>
#include <vector>
// #include <string>
#include <unordered_map>
#include <queue>
#include <string.h>

using namespace std;

typedef struct Classes Classes;
typedef struct Process Process;

struct Process
{
    string task;
    int priority;
};

void intersectionsBetweenCombinationsPM(unordered_map<string, vector<int>> *itensD, unordered_map<string, vector<int>> *classesD, unordered_map<string, vector<int>> *cache, Classes *classes, int *cacheAccess);
void addProcess(Process process);
void printProcessesQueue();
void clearProcessesQueue();

#endif