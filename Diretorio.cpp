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

void Diretorio::identificaBalde(string pseudoChave, int profLocal, int *indSuperior, int *indInferior)
{
    vector<char> indiceDiretorio;
    int profundidadeGlobal = this->profGlobal - 1;
    *indSuperior = *indInferior = 0;
    for (int i = 0; i < profLocal; i++)
    {
        indiceDiretorio.push_back(pseudoChave[i]);
    }

    for (int i = 0; i < profLocal; i++)
    {
        if (this->profGlobal == profLocal)
        {
            *indSuperior += pow(2, profundidadeGlobal);
            *indInferior = *indSuperior;
        }
        else if (indiceDiretorio[i] == '1')
        {
            *indSuperior += pow(2, profundidadeGlobal);
        }
        else
        {
            *indInferior += pow(2, profundidadeGlobal);
        }
        profundidadeGlobal--;
    }
    indiceDiretorio.clear();
}
/*for (int i = 0 ; i < profLocal ; i++)
    {
        if (this->profGlobal == profLocal)
        {
            cout << "SASKPAOSOPAKOS" << endl;
            *indSuperior += pow(2, profundidadeGlobal);
            *indSuperior = *indInferior;
        }
        else
        {
            cout << indiceDiretorio[i] << endl;
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
    }*/
//cout << "indInferior : " << *indInferior << " indSuperior : " << *indSuperior << endl;

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

    /*for (int i = 0; i < balde.getPseudoChave().size(); i++)
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

    if (ind == indice )
    {
        atual->addKey(pseudochave);
    }
    else
    {
        novo->addKey(pseudochave);
    }
/*/
    ind = identificaBits(atual->getPseudoChave()[0], atual->getProfLocal());
    registros[ind] = atual;

    ind = identificaBits(novo->getPseudoChave()[0], novo->getProfLocal());
    registros[ind] = novo;
}

void Diretorio::duplicate(Balde balde, int indice, int profLocal, string pseudoChave)
{
    Balde *atual = new Balde(sizeBalde, profLocal);
    Balde *novo = new Balde(sizeBalde, profLocal);

    int ind = 0;
    int indInferior = 0;
    int indSuperior = 0;

    for (int i = 0; i < registros.size(); i++)
    {
        cout << "Balde : " << i << " Profundidade Local : " << registros[i]->getProfLocal() << endl;
        for (int j = 0; j < registros[i]->getPseudoChave().size(); j++)
        {
            cout << registros[i]->getPseudoChave()[j] << endl;
        }
    }

    cout << endl
         << endl
         << endl
         << endl;

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

    identificaBalde(pseudoChave, profLocal, &indSuperior, &indInferior);
    ind = identificaBits(pseudoChave, registros[indice]->getProfLocal());

    //    cout << "ind : " << ind << " indInferior : " << indInferior << " indSuperior : " << indSuperior << endl;
    //    cout << atual->getPseudoChave().size() <<  endl;

    if (ind == identificaBits(atual->getPseudoChave()[0], atual->getProfLocal()) && sizeBalde > atual->getPseudoChave().size())
    {
        atual->addKey(pseudoChave);
    }
    else
    {
        novo->addKey(pseudoChave);
    }
    Balde *aux;
    cout << "ME DA OQ EU QUERO " << identificaBits(registros[0]->getPseudoChave()[1], registros[1]->getProfLocal()) << endl;

    for (int i = 0; i < registros.size(); i++)
    {

        cout << "Balde : " << i << " Profundidade Local : " << registros[i]->getProfLocal() << endl;
        for (int j = 0; j < registros[i]->getPseudoChave().size(); j++)
        {
            cout << registros[i]->getPseudoChave()[j] << endl;
        }
    }
    cout << "Balde Atual" << endl;
    for (int i = 0; i < atual->getPseudoChave().size(); i++)
    {

        cout << atual->getPseudoChave()[i] << endl;
    }
    cout << "Balde Novo" << endl;
    for (int i = 0; i < novo->getPseudoChave().size(); i++)
    {
        cout << novo->getPseudoChave()[i] << endl;
    }

    cout << endl
         << endl
         << endl
         << endl;

    for (int i = 0; i < pow(2, this->profGlobal); i++)
    {
        for (int j = 0; j < registros[i]->getPseudoChave().size(); j++)
        {
            //cout << "pseudoChave " << registros[i]->getPseudoChave()[j] << "  " << registros[i]->getProfLocal() << endl;
            identificaBalde(registros[i]->getPseudoChave()[j], registros[i]->getProfLocal(), &indSuperior, &indInferior);

            ind = identificaBits(registros[i]->getPseudoChave()[j], registros[i]->getProfLocal());
            //cout << "ind : " << ind << " indInferior : " << indInferior << " indSuperior : " << indSuperior << endl;
            while (indInferior > indSuperior)
            {
                registros[indInferior - 1] = registros[i];
                indInferior--;
            }

            //cout << "ind : " << ind << " indInferior : " << indInferior << " indSuperior : " << indSuperior << endl;
        }

        //cout << endl << endl << endl;
    }

    //cout << "Atual size : " << atual->getPseudoChave().size() << endl;
    //cout << "Novo size : " << novo->getPseudoChave().size() << endl << endl;

    for (int i = 0; i < atual->getPseudoChave().size(); i++)
    {

        ind = identificaBits(atual->getPseudoChave()[i], atual->getProfLocal());
        registros[ind] = atual;
        //cout << ind << endl;
    }

    for (int i = 0; i < novo->getPseudoChave().size(); i++)
    {
        ind = identificaBits(novo->getPseudoChave()[i], novo->getProfLocal());
        registros[ind] = novo;
        //cout << "B" << ind << endl;
    }
    /*
    ind = identificaBits(atual->getPseudoChave()[0], atual->getProfLocal());
    identificaBalde(atual->getPseudoChave()[0], novo->getProfLocal(), &indSuperior, &indInferior);
    cout << "ind : " << ind << " indInferior : " << indInferior << " indSuperior : " << indSuperior << endl;
    ind = identificaBits(atual->getPseudoChave()[1], atual->getProfLocal());
    cout << ind << endl << endl << endl;


    cout << "IND ATUAL AQUI : " << ind << endl ;
    registros[ind] = atual;


    ind = identificaBits(novo->getPseudoChave()[0], novo->getProfLocal());

    cout << "IND NOVO AQUI : " << ind << endl ;

    registros[ind] = novo;
*/

    //cout << "TESTE5 "<< endl << endl;

    /*for( int j = indInferior ; j <= indSuperior ; j++)
    {
        cout << "Atual indice " << indInferior << " " << indSuperior << endl;
        registros[j] = atual;
    }

    identificaBalde(novo->getPseudoChave()[0], novo->getProfLocal(), &indSuperior, &indInferior);
    for( int j = indInferior ; j <= indSuperior ; j++)
    {
        cout << "Novo indice " << indInferior << " " << indSuperior << endl;
        registros[j] = novo;
    }
*/
    cout << "FINALZOU FUNCAO DUPLICATE" << endl << endl;
}
