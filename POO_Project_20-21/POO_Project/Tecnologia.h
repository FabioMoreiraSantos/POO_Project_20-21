#ifndef Tecnologia_HEADER
#define Tecnologia_HEADER

#include <iostream>
#include "Imperio.h"


using namespace std;

class Tecnologia {
    string name;
    int custo = 0;
public:
    Tecnologia(){}
    Tecnologia(string _name): name(_name){} 
    virtual void print() {
        cout << "Custo: " << custo << "   Type: Tecnologia" << endl;
    }
    virtual string getNome() { return name; }
};

class DroneMilitar: public Tecnologia {
public:
    DroneMilitar(): Tecnologia("DroneMilitar") {};
    static int custo;
};
 
class MisseisTeleguiados: public Tecnologia {
public:
    MisseisTeleguiados(): Tecnologia("MisseisTeleguiados") {};
    static int custo;
};

class DefesasTerritoriais: public Tecnologia {
public:
    DefesasTerritoriais(): Tecnologia("DefesasTerritoriais") {};
    static int custo;
};

class BolsaValores: public Tecnologia {
public:
    BolsaValores(): Tecnologia("BolsaValores") {};
    static int custo;
};

class BancoCentral: public Tecnologia {
public:
    BancoCentral(): Tecnologia("BancoCentral") {};
    static int custo;
};

#endif
