#include "producer.hpp"

// dynamic database
int maxSize = 0;

// mutex
mutex mutex1;
mutex mutex4;
mutex mutex5;
long unsigned int commonItensThreadIndex = 0;

void setCommonItensThreadIndex()
{
    commonItensThreadIndex = 0;
}

void parametersCombination(vector<string> *combinations, vector<vector<string>> *commonItens, int maxSize, int *producer_on)
{
    int index = 0;
    int perm[maxSize] = {0};
    vector<string> v;

    while (commonItensThreadIndex < (*commonItens).size())
    {
        std::this_thread::sleep_for(std::chrono::nanoseconds(1));
        mutex1.lock();
        v = (*commonItens)[commonItensThreadIndex];
        commonItensThreadIndex++;
        // std::cout << "i: " << commonItensThreadIndex << "; in thread #" << std::this_thread::get_id() << '\n';
        mutex1.unlock();

        // std::this_thread::sleep_for(std::chrono::nanoseconds(1));
        mutex5.lock();
        for (long unsigned int permutedStringLength = 1; permutedStringLength <= v.size(); permutedStringLength++)
        {
            combination(v, perm, index, v.size(), permutedStringLength, combinations);
        }
        v.clear();
        mutex5.unlock();

    }
    mutex4.lock();
    *producer_on = 0;
    mutex4.unlock();
    // std::this_thread::sleep_for(std::chrono::nanoseconds(1));
}

void combination(vector<string> v, int perm[], int index, int n, int permutedStringLength, vector<string> *combinations)
{
    static int count = 0;

    if (count == permutedStringLength)
    {
        string elements = "";
        for (int i = 0; i < n; i++)
            if (perm[i] == 1)
                elements = elements + v[i] + "|";
        (*combinations).push_back(elements);
    }
    else if ((n - index) >= (permutedStringLength - count))
    {
        perm[index] = 1;
        count++;
        combination(v, perm, index + 1, n, permutedStringLength, combinations);

        perm[index] = 0;
        count--;
        combination(v, perm, index + 1, n, permutedStringLength, combinations);
    }
}