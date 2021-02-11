#include <iostream>
#include <string>
#include <vector>
#include "Balde.h"

using namespace std;

Balde::Balde(int sizeBalde,int profLocal)
{
    this->pseudoChave;
    this->sizeBalde = sizeBalde;
    this->profLocal = profLocal;
}

Balde::~Balde()
{}

void Balde::addProfLocal()
{
    this->profLocal++;
}

int Balde::getProfLocal()
{
    return this->profLocal;
}

vector<string> Balde::getPseudoChave()
{
    return this->pseudoChave;
}

bool Balde::addKey(string chave)
{
    if(this->pseudoChave.size() < this->sizeBalde)
    {
        this->pseudoChave.push_back(chave);
        //cout << "Chave : " << chave << " inserida com sucesso" << endl;
        return true;
    }
    return false;
}
