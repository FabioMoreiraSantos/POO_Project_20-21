#include <iostream>
#include "Territorio.h"
#include "Imperio.h"
#include "Continente.h"
#include <time.h>
#include "Interface.h"

using namespace std;

void initRandom() {
	srand(time(NULL));		//previne repeticoes entre runs
}

int main() {
	Continente * continente = new Continente();
	Planicie* planicie1 = new Planicie();
	Montanha* montanha1 = new Montanha();
	Fortaleza* fortaleza1 = new Fortaleza();
	Mina* mina1 = new Mina();
	Duna* duna1 = new Duna();
	Castelo* castelo1 = new Castelo();

	cout << continente->getNome() << endl << endl;
	cout << planicie1->getNome() << endl;
	cout << planicie1->listaInfo() << endl << endl;
	cout << montanha1->getNome() << endl;
	cout << montanha1->listaInfo() << endl << endl;
	cout << fortaleza1->getNome() << endl;
	cout << fortaleza1->listaInfo() << endl << endl;
	cout << mina1->getNome() << endl;
	cout << mina1->listaInfo() << endl << endl;
	cout << duna1->getNome() << endl;
	cout << duna1->listaInfo() << endl << endl;
	cout << castelo1->getNome() << endl;
	cout << castelo1->listaInfo() << endl << endl;
	return 1;
}

//int main() {
//	initRandom();
//	
//    Interface i(new Mundo(), cin, cout);
//    i.run();
//}