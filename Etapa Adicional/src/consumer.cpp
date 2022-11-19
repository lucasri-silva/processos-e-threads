#include "consumer.hpp"

// mutex
mutex mutex2;
mutex mutex3;
long unsigned int combinationsThreadIndex=0;
// classes
unsigned int irisVersicolor = 0;
unsigned int irisVirginica = 0;
unsigned int irisSetosa = 0;

unordered_map<string, vector<int>> cache;

void setFlowers()
{
    irisVersicolor = 0;
    irisVirginica = 0;
    irisSetosa = 0;
}

void clearCache()
{
    cache.clear();
}

void setCombinationsThreadIndex()
{
    combinationsThreadIndex=0;
}

void intersectionsBetweenCombinations(vector<string> *combinations, unordered_map<string, vector<int>> *itensD, unordered_map<string, vector<int>> *classesD, int *producer_on)
{
    vector<string> keys;
    char *charLine;
    char *token;
    string line;
    unordered_map<string, vector<int>>::const_iterator otherKeysHash;
    unordered_map<string, vector<int>>::const_iterator firstKeyHash;
    string firstKey;
    string cacheKey;
    unsigned int occurrence;

    while((*combinations).size() < 1);
    while(*producer_on || combinationsThreadIndex < (*combinations).size())
    {
        std::this_thread::sleep_for(std::chrono::nanoseconds(1));
        mutex2.lock();
        line = (*combinations)[combinationsThreadIndex];
        combinationsThreadIndex++;
        // cout << (*combinations).size();
        // std::cout << " -- i: " << combinationsThreadIndex << "; in thread #" << std::this_thread::get_id() << '\n';
        charLine = const_cast<char *>(line.c_str());
        token = strtok(charLine, "|");
        cacheKey = "";
        while (token != NULL)
        {
            keys.push_back(token);
            cacheKey = cacheKey + "(" + token + ")";
            token = strtok(NULL, "|");
        }
        if (cacheKey == "")
        {
            combinationsThreadIndex--;
            mutex2.unlock();
            // std::this_thread::sleep_for(std::chrono::nanoseconds(1));
            continue;
        }
        mutex2.unlock();
        // std::this_thread::sleep_for(std::chrono::nanoseconds(1));

        // std::this_thread::sleep_for(std::chrono::nanoseconds(1));
        mutex3.lock();
        if (cache.find(cacheKey) != cache.end())
        {
            computeClassIntersection(cache[cacheKey], *classesD);
        }
        else
        {
            firstKey = keys.back();
            keys.pop_back();
            firstKeyHash = itensD->find(firstKey);
            occurrence = 1;

            for (auto &element : firstKeyHash->second)
            {
                for (auto &key : keys)
                {
                    otherKeysHash = itensD->find(key);
                    for (auto &elementOtherKeys : otherKeysHash->second)
                    {
                        if (element == elementOtherKeys)
                        {
                            occurrence++;
                            break;
                        }
                    }
                }
                if (occurrence == keys.size() + 1)
                {
                    cache[cacheKey].push_back(element);
                }
                occurrence = 1;
            }

            if (cache[cacheKey].size() > 0)
            {
                computeClassIntersection(cache[cacheKey], *classesD);
            }
        }
        keys.clear();
        mutex3.unlock();
        // std::this_thread::sleep_for(std::chrono::nanoseconds(1));
        // while(producer_on && combinationsThreadIndex == (*combinations).size());
    }
}

void printCombinations(vector<string> *combinations)
{
    for (auto &comb : *combinations)
    {
        cout << comb << endl;
    }
}

void computeClassIntersection(vector<int> intersections, unordered_map<string, vector<int>> classesD)
{
    unordered_map<string, vector<int>>::const_iterator versicolor = classesD.find("Iris-versicolor");
    unordered_map<string, vector<int>>::const_iterator virginica = classesD.find("Iris-virginica");
    unordered_map<string, vector<int>>::const_iterator setosa = classesD.find("Iris-setosa");

    bool elementFound = false;

    for (auto &element : intersections)
    {
        elementFound = false;
        for (auto &x : versicolor->second)
        {
            if (element == x)
            {
                irisVersicolor++;
                elementFound = true;
                break;
            }
        }

        if (!elementFound)
        {
            for (auto &y : virginica->second)
            {
                if (element == y)
                {
                    irisVirginica++;
                    elementFound = true;
                    break;
                }
            }
        }

        if (!elementFound)
        {
            for (auto &z : setosa->second)
            {
                if (element == z)
                {
                    irisSetosa++;
                    elementFound = true;
                    break;
                }
            }
        }
    }
}

void classWithGreaterOverlap()
{
    cout << "\n\n---------SOBREPOSIÇÃO DAS INTERSEÇÕES (DAS COMBINAÇÕES) COM CLASSES---------\n";
    cout << "Iris-Versicolor -> " << irisVersicolor << endl;
    cout << "Iris-Virginica -> " << irisVirginica << endl;
    cout << "Iris-Setosa -> " << irisSetosa << endl;
}