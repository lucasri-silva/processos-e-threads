#include "read_database.hpp"

unordered_map<string, vector<int>> itensD;
unordered_map<string, vector<int>> classesD;
unordered_map<string, vector<int>> cache;
queue<vector<string>> itensT;
vector<vector<string>> commonItens;
int maxSize = 0;
int numberOfColumns = 5;
vector<vector<string>> combinations(numberOfColumns - 1);
// classes
unsigned int irisVersicolor = 0;
unsigned int irisVirginica = 0;
unsigned int irisSetosa = 0;

void stop()
{
    cout << "\n\nExecução bem sucedida. Pressione enter para continuar ...";
    while (getchar() != '\n')
        ;
    system("clear");
}

void setFlowers()
{
    irisVersicolor = 0;
    irisVirginica = 0;
    irisSetosa = 0;
}

void clearCombinations()
{
    for(int i=0; i < numberOfColumns-1; i++)
        combinations[i].clear();
}

void clearCache()
{
    cache.clear();
}

void readFileD()
{
    ifstream file;
    string stringLineOutput;
    char *charLineOutput;
    char *token;
    string key;
    int coluna = 1;
    int linha = 1;
    file.open("src/dataset/D.csv");

    if (!file)
    {
        printf("file can't be opened \n");
        return;
    }

    while (file)
    {
        getline(file, stringLineOutput);
        charLineOutput = const_cast<char *>(stringLineOutput.c_str());
        token = strtok(charLineOutput, ",");
        coluna = 1;
        while (token != NULL)
        {
            if (coluna == numberOfColumns)
            {
                key = string(token);
                classesD[key].push_back(linha);
                break;
            }
            key = to_string(coluna) + ", " + string(token);
            itensD[key].push_back(linha);
            token = strtok(NULL, ",");
            coluna++;
        }
        linha++;
    }

    file.close();
    return;
}

void printHashItens()
{
    cout << "-----------------------itensD-----------------------" << endl;
    for (auto mapIt = begin(itensD); mapIt != end(itensD); ++mapIt)
    {
        cout << "(" + mapIt->first + ")"
             << " : ";

        for (auto c : mapIt->second)
            cout << c << " ";

        cout << endl;
    }
}

void printHashClasses()
{
    cout << "-----------------------classesD-----------------------" << endl;
    for (auto mapIt = begin(classesD); mapIt != end(classesD); ++mapIt)
    {
        cout << "(" + mapIt->first + ")"
             << " : ";

        for (auto c : mapIt->second)
            cout << c << " ";

        cout << endl;
    }
}

void readFileT()
{
    ifstream file;
    string stringLineOutput;
    char *charLineOutput;
    char *token;
    string key;
    int coluna = 1;
    int linha = 1;
    vector<string> v;
    file.open("src/dataset/T.csv");

    if (!file)
    {
        printf("file can't be opened \n");
        return;
    }

    while (file)
    {
        getline(file, stringLineOutput);
        charLineOutput = const_cast<char *>(stringLineOutput.c_str());
        token = strtok(charLineOutput, ",");
        coluna = 1;
        while (token != NULL)
        {
            if (coluna == numberOfColumns)
                break;
            key = to_string(coluna) + ", " + string(token);
            v.push_back(key);
            token = strtok(NULL, ",");
            coluna++;
        }
        itensT.push(v);
        v.clear();
        linha++;
    }

    file.close();
    return;
}

void printFileT()
{
    cout << "-----------------------itensT-----------------------" << endl;
    queue<vector<string>> processosBackup = itensT;
    vector<string> v;
    while (!processosBackup.empty())
    {
        v = processosBackup.front();
        processosBackup.pop();
        for (auto &element : v)
            cout << "(" << element << ")"
                 << " ";
        cout << endl;
        v.clear();
    }
    cout << '\n';
}

void saveCommonItens()
{
    queue<vector<string>> itensTBackup = itensT;
    vector<string> v;
    vector<string> y;
    // save all different sizes of the commonsItens
    set<int> sizes;
    while (!itensTBackup.empty())
    {
        v = itensTBackup.front();
        itensTBackup.pop();

        for (auto &element : v)
        {
            if (itensD.find(element) != itensD.end())
                y.push_back(element);
        }
        sizes.insert(y.size());
        commonItens.push_back(y);
        v.clear();
        y.clear();
    }
    // gets the greater size of commonItens
    for (auto &value : sizes)
        if (value > maxSize)
            maxSize = value;
}

void printCommonItens()
{
    cout << "-----------------------VECTOR COM ITENS COMUNS ENTRE T & D-----------------------" << endl;
    for (auto &vec : commonItens)
    {
        for (auto &element : vec)
            cout << "(" << element << ")"
                 << " ";
        cout << endl;
    }
}

void parametersCombination()
{
    int index = 0;
    int perm[maxSize] = {0};
    vector<string> v;

    for (auto &vec : commonItens)
    {
        for (auto &element : vec)
        {
            v.push_back(element);
        }

        for (long unsigned int permutedStringLength = 1; permutedStringLength <= v.size(); permutedStringLength++)
        {
            combination(v, perm, index, v.size(), permutedStringLength);
        }
        v.clear();
    }
}

void combination(vector<string> v, int perm[], int index, int n, int permutedStringLength)
{
    static int count = 0;

    if (count == permutedStringLength)
    {
        string elements = "";
        for (int i = 0; i < n; i++)
            if (perm[i] == 1)
                elements = elements + v[i] + "|";
        (combinations[permutedStringLength - 1]).push_back(elements);
    }
    else if ((n - index) >= (permutedStringLength - count))
    {
        perm[index] = 1;
        count++;
        combination(v, perm, index + 1, n, permutedStringLength);

        perm[index] = 0;
        count--;
        combination(v, perm, index + 1, n, permutedStringLength);
    }
}

void printCombinations()
{
    for (auto &vec : combinations)
    {
        for (auto &element : vec)
            cout << element << endl;
    }
}

void intersectionsBetweenCombinations()
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
    long unsigned int combPos = 0;
    long unsigned int combSize = 0;
    long unsigned int count = 0;
    int combVec = 0;
    int cacheAccess = 0;
    bool hasIntersection;
    int numKeys;
    bool intersectionKeys;
    vector<int> intersectionKeysValues;

    // calculate the total size of vector combinations
    for (int i = 0; i < numberOfColumns - 1; i++)
        combSize = combSize + (combinations[i]).size();

    while (count < combSize)
    {
        intersectionKeysValues.clear();
        hasIntersection = true;
        intersectionKeys = false;
        numKeys = 1;
        line = combinations[combVec][combPos];
        charLine = const_cast<char *>(line.c_str());
        token = strtok(charLine, "|");
        cacheKey = "";
        while (hasIntersection && token != NULL)
        {
            cacheKey = cacheKey + "(" + token + ")";
            if (numKeys > 1 && cache.find(cacheKey) != cache.end())
            {
                cacheAccess++;
                if (cache[cacheKey].size() == 0)
                    hasIntersection = false;
                else
                {
                    intersectionKeys = true;
                    intersectionKeysValues = cache[cacheKey];
                    keys.clear();
                }
            }
            else
                keys.push_back(token);
            numKeys++;
            token = strtok(NULL, "|");
        }
        if (hasIntersection)
        {
            if (cache.find(cacheKey) != cache.end() && cache[cacheKey].size() > 0)
            {
                cacheAccess++;
                computeClassIntersection(cache[cacheKey]);
            }
            else
            {
                if (intersectionKeys)
                {
                    for (auto &element : intersectionKeysValues)
                    {
                        occurrence = 0;
                        for (auto &key : keys)
                        {
                            otherKeysHash = itensD.find(key);
                            for (auto &elementOtherKeys : otherKeysHash->second)
                            {
                                if (element == elementOtherKeys)
                                {
                                    occurrence++;
                                    break;
                                }
                            }
                        }
                        if (occurrence == keys.size())
                            cache[cacheKey].push_back(element);
                    }
                }
                else
                {
                    firstKey = keys.back();
                    keys.pop_back();
                    firstKeyHash = itensD.find(firstKey);
                    for (auto &element : firstKeyHash->second)
                    {
                        occurrence = 0;
                        for (auto &key : keys)
                        {
                            otherKeysHash = itensD.find(key);
                            for (auto &elementOtherKeys : otherKeysHash->second)
                            {
                                if (element == elementOtherKeys)
                                {
                                    occurrence++;
                                    break;
                                }
                            }
                        }
                        if (occurrence == keys.size())
                            cache[cacheKey].push_back(element);
                    }
                }

                if (cache[cacheKey].size() > 0)
                {
                    cacheAccess++;
                    computeClassIntersection(cache[cacheKey]);
                }
            }
            keys.clear();
        }
        count++;
        combPos++;
        if (combPos == combinations[combVec].size())
        {
            combVec++;
            combPos = 0;
        }
    }
    cout << "Número de acesso em cache: " << cacheAccess << endl;
}

void computeClassIntersection(vector<int> intersections)
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
