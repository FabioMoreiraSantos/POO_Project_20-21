#include "Territorio.h"
#include "sstream"

int Territorio::nTerritorios = 1;		//inicializar a variavel static

//Getters
string Territorio::getNome() { return nome; }
int Territorio::getResistencia() { return resistencia; }
int Territorio::getCriacaoProduto() { return criacaoProdutos; }
int Territorio::getCriacaoOuro() { return criacaoOuro; }
int Territorio::getPVitoria() { return pVitoria; }
string Territorio::getStatusConquitado() const { return isConquistado ? "Conquistado" : "Livre"; }
bool Territorio::getIsConquistado() const { return isConquistado; }
int Territorio::getnTerritorios(){ return nTerritorios; }


//Setters
void Territorio::setNome(string name) { nome = name; }
void Territorio::setResistencia(int valor) { resistencia = valor; }
void Territorio::setCriacaoProduto(int valor) { criacaoProdutos = valor; }
void Territorio::setCriacaoOuro(int valor) { criacaoOuro = valor; }
void Territorio::setPVitoria(int valor) { pVitoria = valor; }
void Territorio::setIsConquistado(bool val) { isConquistado = val; }


Territorio::Territorio() {
	nome = "Territorio" + to_string(nTerritorios);
	nTerritorios++;
}

Territorio::Territorio(const Territorio& ref) {
	nTerritorios = ref.nTerritorios;
	nome = ref.nome;
	resistencia = ref.resistencia;
	criacaoProdutos = ref.criacaoProdutos;
	criacaoOuro = ref.criacaoOuro;
	pVitoria = ref.pVitoria;
	isConquistado = ref.isConquistado;
}

Territorio& Territorio::operator=(const Territorio& c) {
	if(this == &c) { return *this; }

	nTerritorios = c.nTerritorios;
	nome = c.nome;
	resistencia = c.resistencia;
	criacaoProdutos = c.criacaoProdutos;
	criacaoOuro = c.criacaoOuro;
	pVitoria = c.pVitoria;
	isConquistado = c.isConquistado;

	return *this;
}
  
string Territorio::listaInfo() const {
	ostringstream os;
  
	os << "Resistencia: " << resistencia << endl
		<< "Criacao Produtos: " << criacaoProdutos << endl
		<< "Criacao Ouro: " << criacaoOuro << endl
		<< "Pontos Vitoria: " << pVitoria << endl
		<< "Status: " << getStatusConquitado();

	return os.str();
}

