#include <iostream>
#include <string>
#include <vector>
#include "Balde.h"
#include "Diretorio.h"


using namespace std;

int main()
{
    Diretorio *teste = new Diretorio(1,2);
    //cout << teste->getRegistros().size() << endl;
    teste->inserts(0);

    
    cout << teste->search(0) << endl;
    return 0;
}