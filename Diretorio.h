#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Diretorio
{
    private:
    int profGlobal;
    int sizeBalde;
    int numBits;
    vector<Balde*> registros;


    public:

    Diretorio(int numBits, int sizeBalde);
    ~Diretorio();


    void addProfGlobal();

    vector<Balde*>getRegistros();


    int identificaBits(string chave, int profLocal);
    void identificaBalde(string pseudoChave, int profLocal, int *indSuperior, int *indInferior);

    string Hashing(int k);

    bool search(int k);
    void inserts(int k);
    
    void split(Balde balde, int indice, string pseudoChave);
    void duplicate(Balde balde, int indice, int profLocal, string pseudoChave);

};