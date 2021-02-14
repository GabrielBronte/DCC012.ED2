#include <string>
#include <vector>

using namespace std;

class Balde
{
    private:
    vector<string> pseudoChave;
    int sizeBalde;
    int profLocal;
    

    public:

    Balde(int sizeBalde, int profLocal);
    ~Balde();

    vector<string>getPseudoChave();
    int getProfLocal();
    bool addKey(string chave);    
    void addProfLocal();
    void setProfLocal();




};