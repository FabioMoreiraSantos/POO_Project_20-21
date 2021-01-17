#ifndef Tecnologia_HEADER
#define Tecnologia_HEADER

#include <iostream>
#include "Imperio.h"


using namespace std;

class Tecnologia {
    string name;
public:
    Tecnologia(){}
    Tecnologia(string _name): name(_name){}
    
    virtual string getNome() { return name; }
};

class DroneMilitar: public Tecnologia {
public:
    DroneMilitar(): Tecnologia("DroneMilitar") {};
    static int custo;
    static string descricao;
};
 
class MisseisTeleguiados: public Tecnologia {
public:
    MisseisTeleguiados(): Tecnologia("MisseisTeleguiados") {};
    static int custo;
    static string descricao;
};

class DefesasTerritoriais: public Tecnologia {
public:
    DefesasTerritoriais(): Tecnologia("DefesasTerritoriais") {};
    static int custo;
    static string descricao;
};

class BolsaValores: public Tecnologia {
public:
    BolsaValores(): Tecnologia("BolsaValores") {};
    static int custo;
    static string descricao;
};

class BancoCentral: public Tecnologia {
public:
    BancoCentral() : Tecnologia("BancoCentral") {};
    static int custo;  
    static string descricao;
};

#endif
