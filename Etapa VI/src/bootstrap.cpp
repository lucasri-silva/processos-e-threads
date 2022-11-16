#include "bootstrap.hpp"

void readFileD(unordered_map<string, vector<int>> *itensD, unordered_map<string, vector<int>> *classesD, int numberOfColumns)
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