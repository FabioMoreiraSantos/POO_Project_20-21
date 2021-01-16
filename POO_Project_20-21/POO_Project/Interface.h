#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include "Mundo.h"
#include "MundoSnapshot.h"
#include <random>

using namespace std;
class Interface {
    static int turno;
    static int ano;
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
    ~Interface();

    void run();

    bool readFromFile(string filename);
    void parseCommand(string command);
    vector<string> splitString(string str) const;
    void setFase(int newFase) { fase = newFase; }

    void nextFase();

    string getFaseName();
    static int getTurnos(); //Static para que nao seja necessario instanciar um objeto
    static int getAno();
    void incrementTurno();


    istream& getIstream() const { return i_stream; }

    // Command methods
    void commandCria(vector<string> commandVector);
    void commandCarrega(vector<string> commandVector);
    void commandLista(vector<string> commandVector);
    void commandConquista(vector<string> commandVector);
    void commandAdquire(vector<string> commandVector);
    void commandModifica(vector<string> commandVector);
    void commandMaisOuro(vector<string> commandVector);
    void commandMaisProd(vector<string> commandVector);
    void commandMaisMilitar(vector<string> commandVector);
    void commandToma(vector<string> commandVector);
    void commandGrava(vector<string> commandVector);
    void commandAtiva(vector<string> commandVector);
    void commandApaga(vector<string> commandVector);

    // Eventos
    void triggerEvent();
    void eventRecursoAbandonado();
    void eventInvasao();
    void eventAliancaDiplomatica();
};