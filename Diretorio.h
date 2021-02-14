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



    vector<Balde*>getRegistros();
    int getProfGlobal();

    int identificaBits(string chave, int profLocal);
    void identificaBalde(Balde balde, int profLocal, int *indSuperior, int *indInferior);
    

    string intToString(int k);

    bool search(int k);
    void inserts(string pseudoChave);
    
    void split(Balde balde, int indice, string pseudoChave);
    void duplicate(Balde balde, int indice, int profLocal, string pseudoChave);

};