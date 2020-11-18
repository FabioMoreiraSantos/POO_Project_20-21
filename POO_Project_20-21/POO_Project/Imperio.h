#include <iostream>

using namespace std;

class Imperio
{
	int armazemProdutos = 0;
	int armazemOuro = 0;
	int maxUnidades = 3;
	int forcaMilitar = 0;
	int maxMilitar = 3;

public:
	Imperio();

	//Getters
	int getMaxUnidades();
	int getMaxMilitar();

	//Setters
	void setMaxUnidades(int maximo);
	void setMaxMilitar(int max);
};

