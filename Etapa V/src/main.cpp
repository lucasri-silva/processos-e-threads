#include "read_database.hpp"

using namespace std;

int main()
{
    system("clear");

    ofstream file;
    file.open("src/result.txt");
    int numExecutions = 0;

    readFileD();
    readFileT();
    saveCommonItens();

    while (numExecutions < 1)
    {
        auto start = chrono::high_resolution_clock::now();
        parametersCombination();
        intersectionsBetweenCombinations();
        auto stop = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = stop - start;
        auto x = chrono::duration_cast<chrono::microseconds>(duration);
        file << to_string(x.count()) << ",";
        numExecutions++;
        classWithGreaterOverlap();
        setFlowers();
        clearCache();
        clearCombinations();
    }
    file.close();

    return 0;
}
