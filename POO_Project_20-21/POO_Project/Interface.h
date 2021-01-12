#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include "Mundo.h"
#include "MundoSnapshot.h"

using namespace std;

class Interface {
    static int turno;
    static const int F_CONFIG = 0;
    static const int F_CONQUISTA = 1;
    static const int F_RECOLHA = 2;
    static const int F_COMPRA = 3;
    static const int F_EVENTOS = 4;

    Mundo* mundo;
    istream& i_stream;
    ostream& o_stream;
    int fase = F_CONFIG;
    vector<MundoSnapshot*> savedSnapshots;
    

public:
    Interface(Mundo* m, istream& _cin, ostream& _cout)
    : mundo(m), i_stream(_cin), o_stream(_cout) {};

    ~Interface() { delete mundo; }

    void run();

    bool readFromFile(string filename);
    void parseCommand(string command);
    vector<string> splitString(string str) const;
    void setFase(int newFase) { fase = newFase; }

    void nextFase();

    string getFaseName();
    static int getTurnos(); //Static para que nao seja necessario instanciar um objeto

    istream& getIstream() const { return i_stream; }
};