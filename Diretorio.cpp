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
    this->profGlobal = numBits;
    this->sizeBalde = sizeBalde;

    Balde *ind = new Balde(sizeBalde,0);

    for( int i=0 ; i < pow(2,numBits) ; i++)
    {
        this->registros.push_back(*ind);
    }
}

Diretorio::~Diretorio()
{}

void Diretorio::addProfGlobal()
{
    this->profGlobal++;
}

vector<Balde>Diretorio::getRegistros(){
    return this->registros;
}

int Diretorio::identificaBits(string chave)
{
    vector<char> indiceDiretorio;
    int indice = 0;
    int j = 0;
    for(int i=0; i < this->profGlobal ; i++)
    {
        indiceDiretorio.push_back(chave[i]);
    }

    for(int i=indiceDiretorio.size()-1; i >=0 ; i--)
    {
        if(indiceDiretorio[i] == '1')
        {
            indice += pow(2,j);
        }
        j++;
    }
    indiceDiretorio.clear();
    return indice;

}

string Diretorio::Hashing(int k)
{
    float knuth = (sqrt(5) - 1) / 2;                      // Sugestão Knuth[1971]
    float parte_fracionaria = (k * knuth) - floor(k * knuth); // kA mod 1
    string pseudochave = bitset<16>(floor(200 * parte_fracionaria)).to_string();
    return pseudochave.substr(10,pseudochave.length());
}

bool Diretorio::search(int k)
{
    string chave = Hashing(k);
    int indice = identificaBits(chave);
    for(int i=0; i < registros[indice].getPseudoChave().size() ; i++)
    {
        if(chave == registros[indice].getPseudoChave()[i])
        {
            return true;
        }
    }
    return false;
}

void Diretorio::inserts(int k)
{
    string chave = Hashing(k);
    int indice = identificaBits(chave);

    if( !registros[indice].addKey(chave) )
    {
        if( this->profGlobal == registros[indice].getProfLocal())
        {
            //duplicate();
        }
        else if( this->profGlobal > registros[indice].getProfLocal())
        {
            //split();
        }
    }
}

void Diretorio::split(Balde chave)
{

}

void Diretorio::duplicate()
{

}
