#include "read_database.hpp"
#include "producer.hpp"
#include "consumer.hpp"
#include <iostream>
#include <sstream>
#include <unistd.h>

using namespace std;

int main()
{
    system("clear");

    unordered_map<string, vector<int>> itensD;
    unordered_map<string, vector<int>> classesD;
    queue<vector<string>> itensT;
    vector<vector<string>> commonItens;
    vector<string> combinations;

    int producer_on = 1;
    int maxSize = 0;

    ofstream file;
    file.open("src/threads-result.txt");
    int numExecutions = 0;
    int numThreads = 5;
    vector<thread> producers;
    vector<thread> consumers;

    readFileD(&itensD, &classesD);
    readFileT(&itensT);
    saveCommonItens(&itensT, &itensD, &commonItens, &maxSize);

    while (numExecutions < 1)
    {
        auto start = chrono::high_resolution_clock::now();
        // parametersCombination(&combinations, &commonItens, maxSize, &producer_on);
        // intersectionsBetweenCombinations(&combinations, &itensD, &classesD, &producer_on);
        for (int i = 0; i < numThreads; i++)
        {
            producers.push_back(thread(parametersCombination, &combinations, &commonItens, maxSize, &producer_on));
            consumers.push_back(thread(intersectionsBetweenCombinations, &combinations, &itensD, &classesD, &producer_on));
        }
        for (int j = 0; j < numThreads; j++)
        {
            producers[j].join();
            consumers[j].join();
        }
        auto stop = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = stop - start;
        auto x = chrono::duration_cast<chrono::microseconds>(duration);
        file << to_string(x.count()) << ",";
        numExecutions++;
        // printCombinations(&combinations);
        classWithGreaterOverlap();
        setCommonItensThreadIndex();
        setCombinationsThreadIndex();
        setFlowers();
        clearCache();
        producers.clear();
        consumers.clear();
        combinations.clear();
        producer_on = 1;
        sleep(0.1);
    }
    file.close();

    return 0;
}
