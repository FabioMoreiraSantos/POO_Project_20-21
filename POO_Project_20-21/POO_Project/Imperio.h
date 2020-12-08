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
	Imperio() = default;

	Imperio(const Imperio& ref) {
		for(auto it = ref.reinado.begin(); it < ref.reinado.end(); it++)
			reinado.push_back((*it));
		
		armazemProdutos = ref.armazemProdutos;
		armazemOuro = ref.armazemOuro;
		maxUnidades = ref.maxUnidades;
		forcaMilitar = ref.forcaMilitar;
		maxMilitar = ref.maxMilitar;
	}

    Imperio& operator=(const Imperio& c) {
        if(this == &c) { return *this; }

        reinado.clear();

		for(auto it = c.reinado.begin(); it < c.reinado.end(); it++)
			reinado.push_back((*it));

		armazemProdutos = c.armazemProdutos;
		armazemOuro = c.armazemOuro;
		maxUnidades = c.maxUnidades;
		forcaMilitar = c.forcaMilitar;
		maxMilitar = c.maxMilitar;

        return *this;
    }


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
	bool conquistar(Territorio * territorio);
	string listaInfo() const;
	string listaConquistados() const;
};

#endif
