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
	//Contrutor por omissao
	// Mundo();
	
	/*
		readMethod => CIN_READ, FILE_READ
	*/
	void criaTerritorio(string type, int quant);
	void configurarMundo();

	void parseComando();

	string getAsString() const;
};

