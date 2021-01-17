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
	int turnoConquistado = 0;
	bool isConquistado = false;

public:
	Territorio();
	Territorio(const Territorio& ref);
    Territorio& operator=(const Territorio& c);
	virtual ~Territorio() {}

	//Getters
	int getResistencia();
	int getCriacaoProduto();
	int getCriacaoOuro();
	int getPVitoria();
	virtual int getTurnoConquistado();
	string getNome();
	string getStatusConquitado() const;
	bool getIsConquistado() const;
	int getnTerritorios();

	//Setters
	void setNome(string name);
	void setResistencia(int valor);
	void setCriacaoProduto(int valor);
	void setCriacaoOuro(int valor);
	void setPVitoria(int valor);
	void setIsConquistado(bool val);
	void setTurnoConquistado(int valor);

	string listaInfo() const;

	template<typename T>
	bool isA() {
		return (dynamic_cast<T*>(this) != NULL);
	}


	virtual void incrementTurnosConquistados() {};
	virtual void changeProductionStats() {};
};

#endif
