#ifndef Territorio_HEADER
#define Territorio_HEADER

#include <iostream>

using namespace std;

class Territorio {
	static int nTerritorios;
	
	string nome;
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

	Territorio(const Territorio& ref) {
		nTerritorios = ref.nTerritorios;
		nome = ref.nome;
		resistencia = ref.resistencia;
		criacaoProdutos = ref.criacaoProdutos;
		criacaoOuro = ref.criacaoOuro;
		pVitoria = ref.pVitoria;
		isConquistado = ref.isConquistado;
	}

    Territorio& operator=(const Territorio& c) {
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

	//Getters
	int getResistencia();
	int getCriacaoProduto();
	int getCriacaoOuro();
	int getPVitoria();
	string getNome();
	string getStatusConquitado() const { return isConquistado ? "Conquistado" : "Livre"; }

	//Setters
	void setResistencia(int valor);
	void setCriacaoProduto(int valor);
	void setCriacaoOuro(int valor);
	void setPVitoria(int valor);
	void setIsConquistado(bool val);

	string listaInfo() const;
};

#endif
