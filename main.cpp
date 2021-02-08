#include <iostream>
#include <string>
#include <vector>
#include "Balde.h"
#include "Diretorio.h"


using namespace std;

int main()
{
    Diretorio *teste = new Diretorio(2,2);
    //cout << teste->getRegistros().size() << endl;
    teste->inserts(65);
    /*for (int i= 0; i< teste->getRegistros().size() ; i++)
    {
        for( int j=0 ; j < 2 ; j++) 
        {
            cout << teste->getRegistros()[i].getPseudoChave()[j] << endl;
        }
    }
    
    */
    cout << teste->search(65) << endl;
    return 0;
}