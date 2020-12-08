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

	Mundo(const Mundo& ref) {
		for(auto it = ref.territorios.begin(); it < ref.territorios.end(); it++)
			territorios.push_back(new Territorio(*(*it)));

		imperio = new Imperio(*(ref.imperio));
		
	}

	~Mundo() {
		// Free allocated territorios' memory
		for(auto it = territorios.begin(); it < territorios.end(); it++)
			delete (*it);
		
		delete imperio;
	}

    Mundo& operator=(const Mundo& c) {
        if(this == &c) { return *this; }

		for(auto it = territorios.begin(); it < territorios.end(); it++)
			delete (*it);

		delete imperio;

        territorios.clear();

		for(auto it = c.territorios.begin(); it < c.territorios.end(); it++)
			territorios.push_back(new Territorio(*(*it)));

		imperio = new Imperio(*(c.imperio));

        return *this;
    }

	bool criaTerritorios(string type, int quant);
	string lista() const;
	string lista(const string nomeTerritorio) const;
	Imperio* getImperio() { return imperio; }

	Territorio* getTerritorioByName(string territorioName);

	string getAsString() const;
};

#endif