#include "primary_memory.hpp"

queue<Process> processes;

void addProcess(Process process)
{
    processes.push(process);
}

void clearProcessesQueue()
{
    processes = queue<Process>();
}

void printProcessesQueue()
{
    queue<Process> processesBackup = processes;
    Process process;
    cout << "Quantidade de processos na memória primária -> " << processes.size() << endl;
    while(!processesBackup.empty())
    {
        process = processesBackup.front();
        cout << process.task << " - " << process.priority << endl;
        processesBackup.pop();
    }
}

void intersectionsBetweenCombinationsPM(unordered_map<string, vector<int>> *itensD, unordered_map<string, vector<int>> *classesD, unordered_map<string, vector<int>> *cache, Classes *classes, int *cacheAccess)
{
    queue<Process> processesBackup = processes;
    Process process;
    vector<string> keys;
    char *charTask;
    char *token;
    string line;
    unordered_map<string, vector<int>>::const_iterator otherKeysHash;
    unordered_map<string, vector<int>>::const_iterator firstKeyHash;
    string firstKey;
    string cacheKey;
    unsigned int occurrence;
    bool hasIntersection;
    int numKeys;
    bool intersectionKeys;
    vector<int> intersectionKeysValues;

    while (!processesBackup.empty())
    {
        intersectionKeysValues.clear();
        hasIntersection = true;
        intersectionKeys = false;
        numKeys = 1;
        process = processesBackup.front();
        processesBackup.pop();
        charTask = const_cast<char *>(process.task.c_str());
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
                (*cacheAccess)++;
                computeClassIntersection((*cache)[cacheKey], classesD, classes);
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

                if ((*cache)[cacheKey].size() > 0)
                {
                    (*cacheAccess)++;
                    computeClassIntersection((*cache)[cacheKey], classesD, classes);
                }
            }
            keys.clear();
        }
    }
    cout << "Número de acesso em cache: " << *cacheAccess << endl;
}