#ifndef Mundo_HEADER
#define Mundo_HEADER


#include <iostream>
#include <vector>
#include "Territorio.h"
#include "Imperio.h"

using namespace std;

class Mundo {
	vector<Territorio*> territorios;
	Imperio* imperio;

public:
	Mundo() {
		imperio = new Imperio();
	};

	~Mundo() {
		// Free allocated territorios' memory
		for(auto it = territorios.begin(); it < territorios.end(); it++)
			delete (*it);
		
		delete imperio;
	}

	bool criaTerritorios(string type, int quant);
	string lista() const;
	string lista(const string nomeTerritorio) const;

	string getAsString() const;
};

#endif