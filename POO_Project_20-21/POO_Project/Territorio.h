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

	//Getters
	int getResistencia();
	int getCriacaoProduto();
	int getCriacaoOuro();
	int getPVitoria();

	//Setters
	void setResistencia(int valor);
	void setCriacaoProduto(int valor);
	void setCriacaoOuro(int valor);
	void setPVitoria(int valor);

};

#endif


