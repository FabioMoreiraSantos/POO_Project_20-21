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
    string name = "DroneMilitar";
public:
    static int custo;
    virtual string getNome() { return name; }
};
 
class MisseisTeleguiados: public Tecnologia {
    string name = "MisseisTeleguiados";
public:
    static int custo;
    virtual string getNome() { return name; }
};

class DefesasTerritoriais: public Tecnologia {
    string name = "DefesasTerritoriais";
public:
    static int custo;
    virtual string getNome() { return name; }
};

class BolsaValores: public Tecnologia {
    string name = "BolsaValores";
public:
    static int custo;
    virtual string getNome() { return name; }
};

class BancoCentral: public Tecnologia {
    string name = "BancoCentral";
public:
    static int custo;
    virtual string getNome() { return name; }
};

#endif
