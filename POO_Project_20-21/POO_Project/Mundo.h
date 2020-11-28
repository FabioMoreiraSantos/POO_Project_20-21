#include <iostream>
#include <vector>
#include "Territorio.h"

using namespace std;

#define CIN_READ 1
#define FILE_READ 2

class Mundo
{
	// const int CIN_READ = 1;
	// const int FILE_READ =
	vector<Territorio*> territorios;

public:
	Mundo() = default;

	~Mundo() {
		// Free allocated territorios' memory
		for(auto it = territorios.begin(); it < territorios.end(); it++)
			delete (*it);
	}

	/*
		readMethod => CIN_READ, FILE_READ
	*/
	bool criaTerritorios(string type, int quant);

	string getAsString() const;
};

