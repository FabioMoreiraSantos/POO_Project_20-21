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
	bool isConquistado = false;

public:
	Territorio() {
		nome = "Territorio" + to_string(nTerritorios);
		nTerritorios++;
	}

	string getNome() const { return nome; };
	int getResistencia() const { return resistencia; };
	int getCriacaoOuro() const { return criacaoOuro; };
	int getCriacaoProdutos() const { return criacaoProdutos; };
	int getPVitoria() const { return pVitoria; };
	string getStatusConquitado() const { return isConquistado ? "Conquistado" : "Livre"; }

	string listaInfo() const;
};


