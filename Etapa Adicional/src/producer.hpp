#ifndef PRODUCER_HPP
#define PRODUCER_HPP
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>

using namespace std;

void parametersCombination(vector<string> *combinations, vector<vector<string>> *commonItens, int maxSize, int *producer_on);
void combination(vector<string> v, int perm[], int index, int n, int permutedStringLength, vector<string> *combinations);

void setCommonItensThreadIndex();

#endif