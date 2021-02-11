#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <bitset>
#include "Balde.h"
#include "Diretorio.h"

using namespace std;

Diretorio::Diretorio(int numBits, int sizeBalde)
{
    this->profGlobal = 1;
    this->numBits = numBits;
    this->sizeBalde = sizeBalde;

    Balde *primeiroBalde = new Balde(sizeBalde, 0);

    for (int i = 0; i < 2; i++)
    {
        this->registros.push_back(primeiroBalde);
    }
}

Diretorio::~Diretorio()
{
}

void Diretorio::addProfGlobal()
{
    this->profGlobal++;
}

vector<Balde *> Diretorio::getRegistros()
{
    return this->registros;
}

int Diretorio::identificaBits(string chave, int profLocal)
{
    vector<char> indiceDiretorio;
    int indice = 0;
    int j = 0;

    for (int i = 0; i < profLocal; i++)
    {
        indiceDiretorio.push_back(chave[i]);
    }

    for (int i = indiceDiretorio.size() - 1; i >= 0; i--)
    {
        if (indiceDiretorio[i] == '1')
        {
            indice += pow(2, j);
        }
        j++;
    }
    indiceDiretorio.clear();
    return indice;
}

void Diretorio::identificaBalde(string pseudoChave, int profLocal, int *indSuperior, int *indInferior)
{
    vector<char> indiceDiretorio;
    int profundidadeGlobal = this->profGlobal - 1;

    for (int i = 0; i < profLocal; i++)
    {
        indiceDiretorio.push_back(pseudoChave[i]);
    }
    
    for (int i = 0 ; i < profLocal ; i++)
    {
        if (this->profGlobal == profLocal)
        {
            *indSuperior += pow(2, profundidadeGlobal);
            *indSuperior = *indInferior;
        }
        else
        {
            if( indiceDiretorio[i] == '1')
            {
                *indSuperior += pow(2, profundidadeGlobal);
            }
            else
            {
                *indInferior += pow(2, profundidadeGlobal);
            }
        }
        profundidadeGlobal--;
    }
}

string Diretorio::Hashing(int k)
{
    string pseudoChave;
    char c;
    for (int i = 0; i < this->numBits; i++)
    {
        c = (k % 2) + '0';
        pseudoChave.push_back(c);
        k = k / 2;
    }
    return pseudoChave;
}

bool Diretorio::search(int k)
{
    string chave = Hashing(k);
    int indice = identificaBits(chave, registros[indice]->getProfLocal());

    for (int i = 0; i < registros[indice]->getPseudoChave().size(); i++)
    {
        if (chave == registros[indice]->getPseudoChave()[i])
        {
            return true;
        }
    }
    return false;
}

void Diretorio::inserts(int k)
{
    string chave = Hashing(k);
    cout << "k = " << k << " " << chave << endl;
    int indice = identificaBits(chave, registros[indice]->getProfLocal());

    if (!registros[indice]->addKey(chave))
    {
        if (this->profGlobal == registros[indice]->getProfLocal())
        {
            registros[indice]->addProfLocal();
            duplicate(*registros[indice], indice, registros[indice]->getProfLocal(), chave);
        }
        else if (this->profGlobal > registros[indice]->getProfLocal())
        {

            registros[indice]->addProfLocal();
            split(*registros[indice], indice, chave);
        }
    }
}

void Diretorio::split(Balde balde, int indice, string pseudochave)
{
    Balde *atual = new Balde(sizeBalde, balde.getProfLocal());
    Balde *novo = new Balde(sizeBalde, balde.getProfLocal());
    int ind = 0;
    int indSuperior;
    int indInferior;

    for (int i = 0; i < balde.getPseudoChave().size(); i++)
    {
        ind = identificaBits(balde.getPseudoChave()[i], registros[indice]->getProfLocal());
        if (ind == indice)
        {
            atual->addKey(balde.getPseudoChave()[i]);
        }
        else
        {
            novo->addKey(balde.getPseudoChave()[i]);
        }
    }
    
    ind = identificaBits(pseudochave, registros[indice]->getProfLocal());
    if (ind == indice)
    {
        atual->addKey(pseudochave);
    }
    else
    {
        novo->addKey(pseudochave);
    }

    ind = identificaBits(atual->getPseudoChave()[0], atual->getProfLocal());
    registros[ind] = atual;

    ind = identificaBits(novo->getPseudoChave()[0], novo->getProfLocal());
    registros[ind] = novo;


}

void Diretorio::duplicate(Balde balde, int indice, int profLocal, string pseudoChave)
{
    Balde *antigoBalde = new Balde(sizeBalde, profLocal);
    Balde *novoBalde = new Balde(sizeBalde, profLocal);
    
    int indInferior = 0;
    int indSuperior = 0;
    for(int i = 0 ; i < pow(2,this->profGlobal); i++)
    {
        this->registros.push_back(novoBalde);
    }
    
    this->profGlobal++;

    //split(balde,indice,pseudoChave);


}
