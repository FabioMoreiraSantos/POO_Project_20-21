#include <iostream>

using namespace std;

class Territorio
{
	static int nTerritorios;
	
	string	nome;
	// int resistencia = 9;
	// int criacaoProdutos = 1;
	// int criacaoOuro = 1;
	// int pVitoria = 0;

	int resistencia;
	int criacaoProdutos;
	int criacaoOuro;
	int pVitoria;

public:
	//Construtor por omissao
	// Territorio(string n) {
	// 	nome = (string) n + to_string(nTerritorios);
	// }
	Territorio(string n) {
		nome = (string) n + to_string(nTerritorios);
		nTerritorios++;
	}

	string getNome();
};


