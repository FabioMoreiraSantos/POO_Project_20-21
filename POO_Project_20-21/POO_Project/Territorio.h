#ifndef Territorio_HEADER
#define Territorio_HEADER

#include <iostream>

using namespace std;

class Territorio
{
	static int nTerritorios;
	
	string	nome;
	int resistencia;
	int criacaoProdutos;
	int criacaoOuro;
	int pVitoria;

public:
	//Construtor por omissao
	Territorio();

	string getNome();
};

#endif


