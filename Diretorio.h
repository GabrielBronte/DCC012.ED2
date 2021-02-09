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


    int identificaBits(string chave);
    string Hashing(int k);

    bool search(int k);
    void inserts(int k);
    
    void split(Balde chave);
    void duplicate();

};