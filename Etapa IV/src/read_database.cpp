#include "read_database.hpp"

unordered_map<string, vector<int>> itensD;
unordered_map<string, vector<int>> classesD;
unordered_map<string, vector<int>> cache;
queue<vector<string>> itensT;
vector<vector<string>> commonItens;
vector<vector<string>> combinations;
int maxSize = 0;
int numberOfColumns = 5;
// classes
unsigned int irisVersicolor = 0;
unsigned int irisVirginica = 0;
unsigned int irisSetosa = 0;

void stop()
{
    cout << "\n\nExecução bem sucedida. Pressione enter para continuar ...";
    while (getchar() != '\n');
    system("clear");
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
    ofstream file;
    file.open("combinations.txt");
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
            combination(&file, v, perm, index, v.size(), permutedStringLength);
        }
        v.clear();
    }
    file.close();
}

void combination(ofstream *file, vector<string> v, int perm[], int index, int n, int permutedStringLength) // int arr[], int data[], int start, int end, int index, int r
{
    static int count = 0;

    if (count == permutedStringLength)
    {
        for (int i = 0; i < n; i++)
            if (perm[i] == 1)
                *file << v[i] << "|";
        *file << "\n";
    }
    else if ((n - index) >= (permutedStringLength - count))
    {
        perm[index] = 1;
        count++;
        combination(file, v, perm, index + 1, n, permutedStringLength);

        perm[index] = 0;
        count--;
        combination(file, v, perm, index + 1, n, permutedStringLength);
    }
}

void intersectionsBetweenCombinations()
{
    fstream file;
    file.open("combinations.txt");
    vector<string> keys;
    char *charLine;
    char *token;
    string line;
    unordered_map<string, vector<int>>::const_iterator otherKeysHash;
    unordered_map<string, vector<int>>::const_iterator firstKeyHash;
    string firstKey;
    string cacheKey;
    unsigned int occurrence;

    while (file)
    {
        getline(file, line);
        charLine = const_cast<char *>(line.c_str());
        token = strtok(charLine, "|");
        cacheKey = "";
        while (token != NULL)
        {
            keys.push_back(token);
            cacheKey = cacheKey + "(" + token + ")";
            token = strtok(NULL, "|");
        }
        if (line == "") break;

        if(cache.find(cacheKey) != cache.end() && cache[cacheKey].size() > 0)
        {
            computeClassIntersection(cache[cacheKey]);
        } else {
            firstKey = keys.back();
            keys.pop_back();
            firstKeyHash = itensD.find(firstKey);
            occurrence = 1;

            for (auto &element : firstKeyHash->second)
            {
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
                if (occurrence == keys.size() + 1)
                {
                    cache[cacheKey].push_back(element);
                }
                occurrence = 1;
            }

            if(cache[cacheKey].size() > 0)
            {
                computeClassIntersection(cache[cacheKey]);
            }
        }
        keys.clear();       
    }
    file.close();
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