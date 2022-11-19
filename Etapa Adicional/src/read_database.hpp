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
#include <chrono>
#include <thread>
#include <mutex>

using namespace std;

void readFileD(unordered_map<string, vector<int>> *itensD, unordered_map<string, vector<int>> *classesD);
void printHashItens(unordered_map<string, vector<int>> *itensD);
void printHashClasses(unordered_map<string, vector<int>> *classesD);

void readFileT(queue<vector<string>> *itensT);
void printFileT(queue<vector<string>> *itensT);
void saveCommonItens(queue<vector<string>> *itensT, unordered_map<string, vector<int>> *itensD, vector<vector<string>> *commonItens, int *maxSize);
void printCommonItens(vector<vector<string>> *commonItens);

void stop();

#endif