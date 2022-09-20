#include "read_database.hpp"
using namespace std;

int main()
{
    system("clear");
    bool on = true;
    unsigned int option;

    while (on)
    {
        cout << "====================\n       MENU\n====================\n";
        cout << "[1] Carregar Itens e Classes (arquivo D)\n";
        cout << "[2] Carregar Itens (arquivo T)\n";
        cout << "[3] Realizar intersecção entre Itens T e Itens D\n";
        cout << "[4] Gerar combinações dos Itens interseccionados\n";
        cout << "[5] Finalizar execução\n";
        cout << ">>> ";
        cin >> option;
        cin.ignore();
        switch (option)
        {
        case 1:
            // Etapa I
            readFileD();
            printHashItens();
            printHashClasses();
            stop();
            break;
        case 2:
            // Etapa II
            readFileT();
            printFileT();
            stop();
            break;
        case 3:
            // Etapa II
            saveCommonItens();
            printCommonItens();
            stop();
            break;
        case 4:
            combination();
            stop();
            break;
        default:
            on = false;
            break;
        }
    }
}