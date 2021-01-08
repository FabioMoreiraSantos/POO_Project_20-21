#ifndef Imperio_HEADER
#define Imperio_HEADER


#include <iostream>
#include <vector>
#include "Territorio.h"
#include <sstream>

using namespace std;

class Imperio
{
	int armazemProdutos = 0;
	int armazemOuro = 0;
	int maxUnidades = 3;
	int forcaMilitar = 3;
	int maxMilitar = 3;
	vector<Territorio*> reinado;				//vetor de territorios

public:
	Imperio(Territorio* territorioInicial);
	Imperio(const Imperio& ref);
    Imperio& operator=(const Imperio& c);

	//Getters
	int getMaxUnidades();
	int getMaxMilitar();
	string getVectorImperio();
	int getReinadoSize();

	//Setters
	void setMaxUnidades(int maximo);
	void setMaxMilitar(int max);
	
	//Methods
	void addTerritorio(Territorio * territorio);
	void removeTerritorio(Territorio * territorio);
	bool conquistar(Territorio * territorio);
	string listaInfo() const;
	string listaConquistados() const;
};

#endif
