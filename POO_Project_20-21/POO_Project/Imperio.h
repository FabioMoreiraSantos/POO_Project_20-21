#ifndef Imperio_HEADER
#define Imperio_HEADER


#include <iostream>
#include <vector>
#include "Territorio.h"
// #include "Tecnologia.h"
#include <sstream>

class Tecnologia;

using namespace std;

class Imperio {
	int armazemProdutos = 3;
	int armazemOuro = 3;
	int forcaMilitar = 2;
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
	int getArmazemProds() { return armazemProdutos; };
	int getForcaMilitar() { return forcaMilitar; };
	int getReinadoSize();
	Territorio* getLastConqueredTerritorio();

	//Setters
	void setMaxUnidades(int maximo);
	void setMaxMilitar(int max);
	void setCanConquistarIlhas(bool val);
	void setCanExchangeProdutosOuro(bool val);
	void setArmazemProdutos(int produtos);
	void setArmazemOuro(int ouro);
	void incrementOuro();
	void incrementProd();
	void incrementForcaMilitar();
	void addOuro(int quant);
	void addProds(int quant);

	
	//Methods
	void addTerritorio(Territorio * territorio);
	void removeTerritorio(Territorio * territorio);
	void recolheMaterias();
	bool conquistar(Territorio * territorio);
	string listaInfo() const;
	string listaConquistados() const;
	string getListaTecnologias() const;
	int adquirirTecnologia(string tecnologia);
	void incrementNDefesasTerritoriais();
	bool hasTecnologiaByName(string nameTecnologia) const;

	int takeTerritorio(Territorio * territorio);
	int takeTecnologia(string nameTecnologia);

	int maisOuro();
	int maisProd();
	int maisMilitar();

	int sufferInvasion(int ano, ostream& o_stream);

	// Comandos Debug
	int modifica(string type, int quant);
	
};

#endif
