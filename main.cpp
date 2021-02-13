#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <math.h>
#include "Balde.h"
#include "Diretorio.h"


using namespace std;

int main()
{
    Diretorio *teste = new Diretorio(6,5);
    //cout << teste->getRegistros().size() << endl;
    //teste->Hashing(2);
    char cont = '1';
    string chave;
    
    for(int i = 1; i <= 40; i++)
    {
        //srand(i) ;
        //teste->inserts(rand() % 59);
        
        chave = teste->Hashing(i+2);
        //chave[0] = cont;
        cout << chave << endl;
        //chave = cont + chave;
        //cout << "i : " << i << endl << endl;
        teste->inserts(chave);
    }

    cout << "Profundidade Global : " << teste->getProfGlobal() << endl << endl;
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