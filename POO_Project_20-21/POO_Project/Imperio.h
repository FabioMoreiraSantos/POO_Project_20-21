#ifndef Imperio_HEADER
#define Imperio_HEADER


#include <iostream>
#include <vector>
#include "Territorio.h"

using namespace std;

class Imperio
{
	int armazemProdutos = 0;
	int armazemOuro = 0;
	int maxUnidades = 3;
	int forcaMilitar = 0;
	int maxMilitar = 3;
	vector<Territorio*> reinado;				//vetor de territorios

public:
	Imperio();

	//Getters
	int getMaxUnidades();
	int getMaxMilitar();
	string getVectorImperio();

	//Setters
	void setMaxUnidades(int maximo);
	void setMaxMilitar(int max);
	
	//Methods
	void addTerritorio(Territorio * territorio);
	void removeTerritorio(Territorio * territorio);
	void conquistar(Territorio * territorio);
};

#endif
