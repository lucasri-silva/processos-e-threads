#include "read_database.hpp"

// dynamic database
int numberOfColumns = 5;

void stop()
{
    cout << "\n\nExecução bem sucedida. Pressione enter para continuar ...";
    while (getchar() != '\n')
        ;
    system("clear");
}

void readFileD(unordered_map<string, vector<int>> *itensD, unordered_map<string, vector<int>> *classesD)
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
                (*classesD)[key].push_back(linha);
                break;
            }
            key = to_string(coluna) + ", " + string(token);
            (*itensD)[key].push_back(linha);
            token = strtok(NULL, ",");
            coluna++;
        }
        linha++;
    }

    file.close();
    return;
}

void printHashItens(unordered_map<string, vector<int>> *itensD)
{
    cout << "-----------------------itensD-----------------------" << endl;
    for (auto mapIt = begin(*itensD); mapIt != end(*itensD); ++mapIt)
    {
        cout << "(" + mapIt->first + ")"
             << " : ";

        for (auto c : mapIt->second)
            cout << c << " ";

        cout << endl;
    }
}

void printHashClasses(unordered_map<string, vector<int>> *classesD)
{
    cout << "-----------------------classesD-----------------------" << endl;
    for (auto mapIt = begin(*classesD); mapIt != end(*classesD); ++mapIt)
    {
        cout << "(" + mapIt->first + ")"
             << " : ";

        for (auto c : mapIt->second)
            cout << c << " ";

        cout << endl;
    }
}

void readFileT(queue<vector<string>> *itensT)
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
    queue<vector<string>> processosBackup = *itensT;
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

void saveCommonItens(queue<vector<string>> *itensT, unordered_map<string, vector<int>> *itensD, vector<vector<string>> *commonItens, int *maxSize)
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
    {
        if (value > *maxSize)
            *maxSize = value;
    }
}

void printCommonItens(vector<vector<string>> *commonItens)
{
    cout << "-----------------------VECTOR COM ITENS COMUNS ENTRE T & D-----------------------" << endl;
    for (auto &vec : *commonItens)
    {
        for (auto &element : vec)
            cout << "(" << element << ")" << " ";
        cout << endl;
    }
}