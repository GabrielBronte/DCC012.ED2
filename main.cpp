#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <math.h>
#include "Balde.h"
#include "Diretorio.h"


using namespace std;


void printfDiretorio(Diretorio *diretorio)
{   
    cout << "Profundidade Global : " << diretorio->getProfGlobal() << endl << endl;
    for(int i = 0 ; i < diretorio->getRegistros().size() ; i++)
    {
        cout << "Balde : " << i << " Profundidade Local : " << diretorio->getRegistros()[i]->getProfLocal() << endl;
        for(int j = 0; j < diretorio->getRegistros()[i]->getPseudoChave().size() ; j++)
        {
            cout << diretorio->getRegistros()[i]->getPseudoChave()[j] << endl;
        }
    }
}

void menu(int bits, int sizeBaldes)
{
    int seleciona;
    do
    {
        cout << "MENU" << endl << endl;
        cout << "[1] Insercoes de 20 pseudo-chaves aleatorias" << endl;
        cout << "[2] Insercoes de 20 pseudo-chaves iniciadas com o bit 0" << endl;
        cout << "[0] Sair" << endl;

        cin >> seleciona ;

        if( ! seleciona )
        {
            break;
        }
        else if ( seleciona == 1)
        {
            Diretorio *diretorio = new Diretorio(bits,sizeBaldes);
            for(int i = 1; i <= 20; i++)
            {
                string chave;
                srand(time(0));
                chave = diretorio->intToString(rand() % 100 + i);

                diretorio->inserts( chave ) ;
            }
            printfDiretorio(diretorio);
            delete diretorio;
        }
        else
        {
            Diretorio *diretorio = new Diretorio(bits,sizeBaldes);
            for(int i = 1; i <= 20; i++)
            {
                string chave;

                char primeiroBit = '0';

                srand(time(0));
                chave = diretorio->intToString(rand() % 59 + i);
                chave [0] = primeiroBit;

                diretorio->inserts( chave ) ;
            }

            printfDiretorio(diretorio);

            delete diretorio;

        }
        cout << endl << endl << endl;
    } while (seleciona != 0);
}

int main()
{
    int bits, sizeBaldes;

    cout << "Digite o tamanho dos baldes : " ;
    cin >> sizeBaldes;
    cout << "Digite o numero de bits : ";
    cin >> bits;
    cout << endl;
    
    menu(bits, sizeBaldes);

    return 0;
}