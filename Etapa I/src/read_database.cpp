#include "read_database.hpp"

unordered_map<string, vector<int>> itens;
unordered_map<string, vector<int>> classes;

void readFile(string fileName)
{
    ifstream file;
    string stringLineOutput;
    char *charLineOutput;
    char *token;
    string key;
    int coluna = 1;
    int linha = 1;
    vector<int> v;
    file.open("src/dataset/" + fileName);

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
            if (coluna == 5) {
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

void imprimeHashItens()
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

void imprimeHashClasses() 
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