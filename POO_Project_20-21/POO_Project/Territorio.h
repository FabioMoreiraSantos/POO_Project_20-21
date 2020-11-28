#include <iostream>

using namespace std;

class Territorio
{
	static int nTerritorios;
	
	string	nome;
	int resistencia = 9;
	int criacaoProdutos = 1;
	int criacaoOuro = 1;
	int pVitoria = 0;

public:
	Territorio() {
		nome = "Territorio" + to_string(nTerritorios);
		nTerritorios++;
	}

	string getNome();
};


