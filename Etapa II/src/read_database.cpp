#include "read_database.hpp"

unordered_map<string, vector<int>> itens;
unordered_map<string, vector<int>> classes;
vector<string> commonItens;
queue<vector<string>> processos;

void stop()
{
    cout << "\n\nPressione enter para continuar ...";
    while (getchar() != '\n');
    cout << endl << endl;
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
                classes[key].push_back(linha);
                break;
            }
            key = to_string(coluna) + ", " + string(token);
            itens[key].push_back(linha);
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
    cout << "-----------------------ITENS-----------------------" << endl;
    for (auto mapIt = begin(itens); mapIt != end(itens); ++mapIt)
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
    cout << "-----------------------CLASSES-----------------------" << endl;
    for (auto mapIt = begin(classes); mapIt != end(classes); ++mapIt)
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
        processos.push(v);
        v.clear();
        linha++;
    }

    file.close();
    return;
}

void printFileT()
{
    cout << "-----------------------PROCESSOS-----------------------" << endl;
    queue<vector<string>> processosBackup = processos;
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
    queue<vector<string>> processosBackup = processos;
    vector<string> v;
    while (!processosBackup.empty())
    {
        v = processosBackup.front();
        processosBackup.pop();
        for (auto &element : v)
        {
            if(itens.find(element) != itens.end())
                commonItens.push_back(element);
        }
        v.clear();
    }
}

void printCommonItens()
{   
    cout << "-----------------------VECTOR COM ITENS COMUNS ENTRE ITENS T & D-----------------------" << endl;
    for(auto &element : commonItens)
        cout << element << endl;
}

void combinations()
{
    ofstream file;
    file.open("combinations.txt");
    vector<string> v;
    for(auto &element : commonItens)
    {
        v.push_back(element);
        for(auto &value : v)
            file << "(" << value << ")" << " ";
        file << endl;
    }
}