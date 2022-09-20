#include "read_database.hpp"

unordered_map<string, vector<int>> itensD;
unordered_map<string, vector<int>> classesD;
queue<vector<string>> itensT;
vector<vector<string>> commonItens;
vector<vector<string>> combinations;

void stop()
{
    cout << "\n\nExecução bem sucedida. Pressione enter para continuar ...";
    while (getchar() != '\n')
        ;
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
            if (coluna == 5)
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
            if (coluna == 5)
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
    while (!itensTBackup.empty())
    {
        v = itensTBackup.front();
        itensTBackup.pop();
        for (auto &element : v)
        {
            if (itensD.find(element) != itensD.end())
                y.push_back(element);
        }
        commonItens.push_back(y);
        v.clear();
        y.clear();
    }
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

void combination() // int arr[], int data[], int start, int end, int index, int r
{
    ofstream file;
    file.open("combinations.txt");
    unsigned int currentSize = 1;
    unsigned int currentIndex;
    vector<string> v;

    for (auto &vec : commonItens)
    {
        for (auto &element : vec)
        {
            v.push_back(element);
        }
        for (long unsigned int i = 0; i < v.size(); i++)
        {
            currentIndex=0;
            for (long unsigned int j = 0; j < v.size(); j++)
            {
                if(currentIndex == currentSize)
                {
                    file << ", ";
                    currentIndex = 0;
                    j = j - currentSize + 1;
                }
                file << "(" << v[j] << ")" << "";
                currentIndex++;
            }
            file << ", ";
            currentSize++;
        }
        file << endl;
        currentSize=1;
        v.clear();
    }
}