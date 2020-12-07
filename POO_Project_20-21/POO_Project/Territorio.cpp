#include "Territorio.h"
#include "sstream"

int Territorio::nTerritorios = 1;		//inicializar a variavel static

string Territorio::listaInfo() const {
	ostringstream os;

	os << "Resistencia: " << resistencia << endl
		<< "Criacao Produtos: " << criacaoProdutos << endl
		<< "Criacao Ouro: " << criacaoOuro << endl
		<< "Pontos Vitoria: " << pVitoria << endl
		<< "Status: " << getStatusConquitado();

	return os.str();
}

