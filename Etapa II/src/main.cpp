#include "read_database.hpp"
using namespace std;

int main()
{
    // Etapa I
    readFileD();
    printHashItens();
    printHashClasses();
    stop();

    // Etapa II
    readFileT();
    printFileT();
    saveCommonItens();
    printCommonItens();
    combinations();
    stop();

}