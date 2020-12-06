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

//Getters
string Territorio::getNome()
{
	return nome;
}

int Territorio::getResistencia()
{
	return resistencia;
}

int Territorio::getCriacaoProduto()
{
	return criacaoProdutos;
}

int Territorio::getCriacaoOuro()
{
	return criacaoOuro;
}

int Territorio::getPVitoria()
{
	return pVitoria;
}


//Setters
void Territorio::setResistencia(int valor)
{
	resistencia = valor;
}

void Territorio::setCriacaoProduto(int valor)
{
	criacaoProdutos = valor;
}

void Territorio::setCriacaoOuro(int valor)
{
	criacaoOuro = valor;
}

void Territorio::setPVitoria(int valor)
{
	pVitoria = valor;
}


