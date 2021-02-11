#include <iostream>
#include <string>
#include <vector>
#include "Balde.h"
#include "Diretorio.h"


using namespace std;

int main()
{
    Diretorio *teste = new Diretorio(8,2);
    //cout << teste->getRegistros().size() << endl;
    //teste->Hashing(2);
    teste->inserts(0);
    teste->inserts(7);
    teste->inserts(250);
    teste->inserts(1);
    teste->inserts(12);
    for(int i = 0 ; i < teste->getRegistros().size() ; i++)
    {
        cout << "Balde : " << i << " Profundidade Local : " << teste->getRegistros()[i]->getProfLocal() << endl;
        for(int j = 0; j < teste->getRegistros()[i]->getPseudoChave().size() ; j++)
        {
            cout << teste->getRegistros()[i]->getPseudoChave()[j] << endl;
        }
    }


    
    
    //cout << teste->search(0) << endl;
    return 0;
}