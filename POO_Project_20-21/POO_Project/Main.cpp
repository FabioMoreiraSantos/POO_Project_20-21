#include <iostream>
#include "Territorio.h"
#include "Imperio.h"
#include <time.h>
#include "Interface.h"
#include "Tecnologia.h"

using namespace std;

void initRandom() {
	srand(time(NULL));		//previne repeticoes entre runs
}

int main() {
	initRandom();
	
    Interface i(new Mundo(), cin, cout);
    i.run();

    // Imperio i1(new Territorio);

    // // Imperio i2(i1);
    // // Imperio i3 = i2;

    // i1.adquirirTecnologia("banco_central");
    // i1.adquirirTecnologia("drone_militar");
    // i1.adquirirTecnologia("misseis_teleguiados");
    // i1.adquirirTecnologia("bolsa_de_valores");



    // DroneMilitar dm();
    // BolsaValores bv();
    // MisseisTeleguiados mt();
    // DefesasTerritoriais dt();
    // BancoCentral bc();
}
