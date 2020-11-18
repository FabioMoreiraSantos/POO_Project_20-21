#include "Territorio.h"
#include "sstream"

int Territorio::nTerritorios = 1;		//inicializar a variavel static

//Construtor por omissao
Territorio::Territorio()
{
	nome = "Territorio" + to_string(nTerritorios);		//Concatenar String com Int
	resistencia = 9;
	criacaoOuro = 1;
	criacaoProdutos = 1;
	pVitoria = 0;
	nTerritorios++;
}

string Territorio::getNome()
{
	return nome;
}


