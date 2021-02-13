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

int Diretorio::getProfGlobal()
{
    return this->profGlobal;
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

void Diretorio::identificaBalde(Balde balde, int profLocal, int *indSuperior, int *indInferior)
{
    vector<char> indiceDiretorio;
    int profundidadeGlobal = this->profGlobal - 1;
    *indSuperior = *indInferior = 0;
    int indRetornado = 0;
    int indMaximo = indRetornado;
    int indMin = 0;
    int flag = 0;

    if (this->profGlobal == balde.getProfLocal())
    {
        *indSuperior = *indInferior = identificaBits(balde.getPseudoChave()[0], balde.getProfLocal());
        return;
    }
    for (int i = 0; i < profLocal; i++)
    {
        indiceDiretorio.push_back(balde.getPseudoChave()[i][i]);
    }

    for (int i = 0; i < indiceDiretorio.size() ; i++)
    {
        if (indiceDiretorio[i] == '1')
        {
            indMin += pow(2, profundidadeGlobal);
        }
        profundidadeGlobal--;
    }

    *indInferior = indMin;
    *indSuperior = indMin +1 ;



    indiceDiretorio.clear();
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

void Diretorio::inserts(string pseudoChave)
{
    //cout << pseudoChave << endl;
    int indice = identificaBits(pseudoChave, registros[indice]->getProfLocal());

    if (!registros[indice]->addKey(pseudoChave))
    {
        if (this->profGlobal == registros[indice]->getProfLocal())
        {
            registros[indice]->addProfLocal();
            if (this->profGlobal < numBits)
            {
                duplicate(*registros[indice], indice, registros[indice]->getProfLocal(), pseudoChave);
            }
            else
                cout << "ERRO ! " << endl;
            return;
        }
        else if (this->profGlobal > registros[indice]->getProfLocal())
        {

            registros[indice]->addProfLocal();
            split(*registros[indice], indice, pseudoChave);
        }
    }
}

void Diretorio::split(Balde balde, int indice, string pseudoChave)
{
    Balde *atual = new Balde(sizeBalde, balde.getProfLocal());
    Balde *novo = new Balde(sizeBalde, balde.getProfLocal());

    int ind = 0;
    int indAtual = 0;

    atual->addKey(balde.getPseudoChave()[0]);

    indAtual = identificaBits(atual->getPseudoChave()[0], atual->getProfLocal());

    for (int i = 1; i < balde.getPseudoChave().size(); i++)
    {
        ind = identificaBits(balde.getPseudoChave()[i], registros[indice]->getProfLocal());

        if (ind == indAtual)
        {
            atual->addKey(balde.getPseudoChave()[i]);
        }
        else
        {
            novo->addKey(balde.getPseudoChave()[i]);
        }
    }

    ind = identificaBits(pseudoChave, registros[indice]->getProfLocal());

    if (ind == indAtual)
    {
        atual->addKey(pseudoChave);
    }
    else
    {
        novo->addKey(pseudoChave);
    }

    ind = identificaBits(atual->getPseudoChave()[0], atual->getProfLocal());
    registros[ind] = atual;

    ind = identificaBits(novo->getPseudoChave()[0], novo->getProfLocal());
    registros[ind] = novo;
}

void Diretorio::duplicate(Balde balde, int indice, int profLocal, string pseudoChave)
{
    vector<Balde *> diretorio ;

    Balde *atual = new Balde(sizeBalde, profLocal);
    Balde *novo = new Balde(sizeBalde, profLocal);
    Balde *vazio = new Balde(sizeBalde, profLocal);

    int ind = 0;
    int indInferior = 0;
    int indSuperior = 0;

    for(int i = 0 ; i < registros.size()*2 ; i++)
    {
        diretorio.push_back(vazio);
    }

    for (int i = 0; i < pow(2, this->profGlobal); i++)
    {
        this->registros.push_back(novo);
    }

    this->profGlobal++;

    atual->addKey(balde.getPseudoChave()[0]);

    for (int i = 1; i < balde.getPseudoChave().size(); i++)
    {
        ind = identificaBits(balde.getPseudoChave()[i], registros[indice]->getProfLocal());

        if (ind == identificaBits(atual->getPseudoChave()[0], atual->getProfLocal()))
        {
            atual->addKey(balde.getPseudoChave()[i]);
        }
        else
        {
            novo->addKey(balde.getPseudoChave()[i]);
        }
    }
    ind = identificaBits(pseudoChave, registros[indice]->getProfLocal());

    if (ind == identificaBits(atual->getPseudoChave()[0], atual->getProfLocal()) && sizeBalde > atual->getPseudoChave().size())
    {
        atual->addKey(pseudoChave);
    }
    else
    {
        novo->addKey(pseudoChave);
    }

    for (int i = 0; i < sqrt(registros.size()) ; i++)
    {

        identificaBalde(*registros[i], registros[i]->getProfLocal(), &indSuperior, &indInferior);
        if (indSuperior == indInferior)
        {
            diretorio[indSuperior] = registros[i];
        }
        else
        {
            while (indInferior <= indSuperior)
            {
                diretorio[indInferior] = registros[i];
                indInferior++;
            }
        }
    }
    diretorio[identificaBits(atual->getPseudoChave()[0], atual->getProfLocal())] = atual;

    diretorio[identificaBits(novo->getPseudoChave()[0], novo->getProfLocal())] = novo;

    registros = diretorio;

}
