#include "bootstrap.hpp"
#include "newdata.hpp"
#include "primary_memory.hpp"

using namespace std;

int main()
{
    system("clear");

    unordered_map<string, vector<int>> itensD;
    unordered_map<string, vector<int>> classesD;
    queue<vector<string>> itensT;
    vector<vector<string>> commonItens;
    int numberOfColumns = 5;
    vector<vector<string>> combinations(numberOfColumns-1);
    unordered_map<string, vector<int>> cache;
    Classes classes;
    int cacheAccess = 0;
    
    ofstream file;
    file.open("src/time-execution.txt");
    int numExecutions = 0;

    readFileD(&itensD, &classesD, numberOfColumns);
    readFileT(&itensT, numberOfColumns);
    saveCommonItens(&commonItens, &itensT, &itensD);

    while (numExecutions < 1)
    {
        auto start = chrono::high_resolution_clock::now();
        parametersCombination(&combinations, &commonItens);
        intersectionsBetweenCombinations(&combinations, numberOfColumns, &itensD, &classesD, &cache, &classes, &cacheAccess);
        intersectionsBetweenCombinationsPM(&itensD, &classesD, &cache, &classes, &cacheAccess);
        auto stop = chrono::high_resolution_clock::now();
        printProcessesQueue();
        classWithGreaterOverlap(&classes);
        chrono::duration<double> duration = stop - start;
        auto x = chrono::duration_cast<chrono::microseconds>(duration);
        file << to_string(x.count()) << ",";
        for(long unsigned int i=0; i < combinations.size(); i++) combinations[i].clear();
        cache.clear();
        cacheAccess = 0;
        clearClasses(&classes);
        clearProcessesQueue();
        numExecutions++;
    }
    file.close();

    return 0;
}
