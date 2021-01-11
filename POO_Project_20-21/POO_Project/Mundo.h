#ifndef Mundo_HEADER
#define Mundo_HEADER


#include <iostream>
#include <vector>
#include "Territorio.h"
#include "Continente.h"
#include "Ilha.h"
#include "Imperio.h"

using namespace std;

class Mundo {
	vector<Territorio*> territorios;
	Imperio* imperio;

public:
	Mundo();
	Mundo(const Mundo& ref);
	~Mundo();

    Mundo& operator=(const Mundo& c);

	bool criaTerritorios(string type, int quant);
	string lista() const;
	string lista(const string nomeTerritorio) const;
	Imperio* getImperio() { return imperio; }
	Territorio* getTerritorioByName(string territorioName);
	string getAsString() const;
	int imperioAdquireTecnologia(string nomeTecnologia);
	int tomaCommand(string type, string name);

};

#endif