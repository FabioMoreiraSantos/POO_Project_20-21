#include "Territorio.h"
#include "sstream"

int Territorio::nTerritorios = 1;		//inicializar a variavel static

//Getters
string Territorio::getNome() { return nome; }
int Territorio::getResistencia() { return resistencia; }
int Territorio::getCriacaoProduto() { return criacaoProdutos; }
int Territorio::getCriacaoOuro() { return criacaoOuro; }
int Territorio::getPVitoria() { return pVitoria; }

//Setters
void Territorio::setResistencia(int valor) { resistencia = valor; }
void Territorio::setCriacaoProduto(int valor) { criacaoProdutos = valor; }
void Territorio::setCriacaoOuro(int valor) { criacaoOuro = valor; }
void Territorio::setPVitoria(int valor) { pVitoria = valor; }
  
string Territorio::listaInfo() const {
	ostringstream os;
  
	os << "Resistencia: " << resistencia << endl
		<< "Criacao Produtos: " << criacaoProdutos << endl
		<< "Criacao Ouro: " << criacaoOuro << endl
		<< "Pontos Vitoria: " << pVitoria << endl
		<< "Status: " << getStatusConquitado();

	return os.str();
}

