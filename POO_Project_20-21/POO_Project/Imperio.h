#ifndef Imperio_HEADER
#define Imperio_HEADER


#include <iostream>
#include <vector>
#include "Territorio.h"
// #include "Tecnologia.h"
#include <sstream>

class Tecnologia;

using namespace std;

class Imperio
{

	int armazemProdutos = 0;
	int armazemOuro = 10;
	int forcaMilitar = 6;
	int maxUnidades = 3;
	int maxMilitar = 3;

	bool canConquistarIlhas = false;
	bool canExchangeProdutosOuro = false;
	int nDefesasTerritoriais = 0;
	
	vector<Territorio*> reinado;				//vetor de territorios
	vector<Tecnologia*> tecnologias; 

public:
	Imperio(Territorio* territorioInicial);
	Imperio(const Imperio& ref);
    Imperio& operator=(const Imperio& c);

	//Getters
	int getMaxUnidades();
	int getMaxMilitar();
	string getVectorImperio();
	int getArmazemOuro() { return armazemOuro; };

	//Setters
	void setMaxUnidades(int maximo);
	void setMaxMilitar(int max);
	void setCanConquistarIlhas(bool val);
	void setCanExchangeProdutosOuro(bool val);
	
	//Methods
	void addTerritorio(Territorio * territorio);
	void removeTerritorio(Territorio * territorio);
	bool conquistar(Territorio * territorio);
	string listaInfo() const;
	string listaConquistados() const;
	bool adquirirTecnologia(string tecnologia);
	void incrementNDefesasTerritoriais();
};

#endif
