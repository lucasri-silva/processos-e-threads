#include "newdata.hpp"

int maxSize = 0;

void stop()
{
    cout << "\n\nExecução bem sucedida. Pressione enter para continuar ...";
    while (getchar() != '\n');
    system("clear");
}

void clearClasses(Classes *classes)
{
    classes->irisSetosa = 0;
    classes->irisVersicolor = 0;
    classes->irisVirginica = 0;
}

bool verifyTimeExecProcess(chrono::_V2::system_clock::time_point start, chrono::_V2::system_clock::time_point stop, string task, int priority)
{
    // ofstream file;
    // file.open("src/time-execution-individual-tasks.txt", ios_base::app);
    Process stopped_process;
    chrono::duration<double> duration = stop - start;
    auto timeExecProcessNano = chrono::duration_cast<chrono::nanoseconds>(duration);
    auto timeLimitProcessNano = chrono::duration_cast<chrono::nanoseconds>(chrono::duration<double>(1.3200e-05)); // = 0.0000132 seconds = 13200 nanoseconds
    // file << to_string(timeExecProcessNano.count()) << ",";
    // file.close();

    if (timeExecProcessNano > timeLimitProcessNano)
    {
        stopped_process.task = task;
        stopped_process.priority = priority;
        addProcess(stopped_process);
        return true;
    }
    return false;
}

void readFileT(queue<vector<string>> *itensT, int numberOfColumns)
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
        (*itensT).push(v);
        v.clear();
        linha++;
    }

    file.close();
    return;
}

void printFileT(queue<vector<string>> *itensT)
{
    cout << "-----------------------itensT-----------------------" << endl;
    queue<vector<string>> processosBackup = (*itensT);
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

void saveCommonItens(vector<vector<string>> *commonItens, queue<vector<string>> *itensT, unordered_map<string, vector<int>> *itensD)
{
    queue<vector<string>> itensTBackup = *itensT;
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
            if ((*itensD).find(element) != (*itensD).end())
                y.push_back(element);
        }
        sizes.insert(y.size());
        (*commonItens).push_back(y);
        v.clear();
        y.clear();
    }
    // gets the greater size of commonItens
    for (auto &value : sizes)
        if (value > maxSize)
            maxSize = value;
}

void printCommonItens(vector<vector<string>> *commonItens)
{
    cout << "-----------------------VECTOR COM ITENS COMUNS ENTRE T & D-----------------------" << endl;
    for (auto &vec : *commonItens)
    {
        for (auto &element : vec)
            cout << "(" << element << ")"
                 << " ";
        cout << endl;
    }
}

void parametersCombination(vector<vector<string>> *combinations, vector<vector<string>> *commonItens)
{
    int index = 0;
    int perm[maxSize] = {0};
    vector<string> v;

    for (auto &vec : *commonItens)
    {
        for (auto &element : vec)
        {
            v.push_back(element);
        }

        for (long unsigned int permutedStringLength = 1; permutedStringLength <= v.size(); permutedStringLength++)
        {
            combination(combinations, v, perm, index, v.size(), permutedStringLength);
        }
        v.clear();
    }
}

void combination(vector<vector<string>> *combinations, vector<string> v, int perm[], int index, int n, int permutedStringLength)
{
    static int count = 0;

    if (count == permutedStringLength)
    {
        string elements = "";
        for (int i = 0; i < n; i++)
            if (perm[i] == 1)
                elements = elements + v[i] + "|";
        (*combinations)[permutedStringLength - 1].push_back(elements);
    }
    else if ((n - index) >= (permutedStringLength - count))
    {
        perm[index] = 1;
        count++;
        combination(combinations, v, perm, index + 1, n, permutedStringLength);

        perm[index] = 0;
        count--;
        combination(combinations, v, perm, index + 1, n, permutedStringLength);
    }
}

void printCombinations(vector<vector<string>> *combinations)
{
    for (auto &vec : *combinations)
    {
        for (auto &element : vec)
            cout << element << endl;
    }
}

void intersectionsBetweenCombinations(vector<vector<string>> *combinations, int numberOfColumns, unordered_map<string, vector<int>> *itensD, unordered_map<string, vector<int>> *classesD, unordered_map<string, vector<int>> *cache, Classes *classes, int *cacheAccess)
{
    vector<string> keys;
    char *charTask;
    char *token;
    string task;
    unordered_map<string, vector<int>>::const_iterator otherKeysHash;
    unordered_map<string, vector<int>>::const_iterator firstKeyHash;
    string firstKey;
    string cacheKey;
    unsigned int occurrence;
    long unsigned int combPos = 0;
    long unsigned int combSize = 0;
    long unsigned int count = 0;
    int priority = 0;
    bool hasIntersection;
    int numKeys;
    bool intersectionKeys;
    vector<int> intersectionKeysValues;

    // calculate the total size of vector combinations
    for (int i = 0; i < numberOfColumns - 1; i++)
        combSize = combSize + (*combinations)[i].size();

    while (count < combSize)
    {
        auto start = chrono::high_resolution_clock::now();
        intersectionKeysValues.clear();
        hasIntersection = true;
        intersectionKeys = false;
        numKeys = 1;
        task = (*combinations)[priority][combPos];
        charTask = const_cast<char *>(task.c_str());
        token = strtok(charTask, "|");
        cacheKey = "";
        while (hasIntersection && token != NULL)
        {
            cacheKey = cacheKey + "(" + token + ")";
            if (numKeys > 1 && (*cache).find(cacheKey) != (*cache).end())
            {
                (*cacheAccess)++;
                if ((*cache)[cacheKey].size() == 0)
                    hasIntersection = false;
                else
                {
                    intersectionKeys = true;
                    intersectionKeysValues = (*cache)[cacheKey];
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
            if ((*cache).find(cacheKey) != (*cache).end() && (*cache)[cacheKey].size() > 0)
            {
                auto stop = chrono::high_resolution_clock::now();
                if (!verifyTimeExecProcess(start, stop, (*combinations)[priority][combPos], priority))
                {
                    (*cacheAccess)++;
                    computeClassIntersection((*cache)[cacheKey], classesD, classes);
                }
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
                            otherKeysHash = (*itensD).find(key);
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
                            (*cache)[cacheKey].push_back(element);
                    }
                }
                else
                {
                    firstKey = keys.back();
                    keys.pop_back();
                    firstKeyHash = (*itensD).find(firstKey);
                    for (auto &element : firstKeyHash->second)
                    {
                        occurrence = 0;
                        for (auto &key : keys)
                        {
                            otherKeysHash = (*itensD).find(key);
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
                            (*cache)[cacheKey].push_back(element);
                    }
                }
                auto stop = chrono::high_resolution_clock::now();
                if (!verifyTimeExecProcess(start, stop, (*combinations)[priority][combPos], priority) && (*cache)[cacheKey].size() > 0)
                {
                    (*cacheAccess)++;
                    computeClassIntersection((*cache)[cacheKey], classesD, classes);
                }
            }
            keys.clear();
        }
        count++;
        combPos++;
        if (combPos == (*combinations)[priority].size())
        {
            priority++;
            combPos = 0;
        }
    }
}

void computeClassIntersection(vector<int> intersections, unordered_map<string, vector<int>> *classesD, Classes *classes)
{
    unordered_map<string, vector<int>>::const_iterator versicolor = (*classesD).find("Iris-versicolor");
    unordered_map<string, vector<int>>::const_iterator virginica = (*classesD).find("Iris-virginica");
    unordered_map<string, vector<int>>::const_iterator setosa = (*classesD).find("Iris-setosa");

    bool elementFound = false;

    for (auto &element : intersections)
    {
        elementFound = false;
        for (auto &x : versicolor->second)
        {
            if (element == x)
            {
                classes->irisVersicolor++;
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
                    classes->irisVirginica++;
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
                    classes->irisSetosa++;
                    elementFound = true;
                    break;
                }
            }
        }
    }
}

void classWithGreaterOverlap(Classes *classes)
{
    cout << "\n\n---------SOBREPOSIÇÃO DAS INTERSEÇÕES (DAS COMBINAÇÕES) COM CLASSES---------\n";
    cout << "Iris-Versicolor -> " << classes->irisVersicolor << endl;
    cout << "Iris-Virginica -> " << classes->irisVirginica << endl;
    cout << "Iris-Setosa -> " << classes->irisSetosa << endl;
}