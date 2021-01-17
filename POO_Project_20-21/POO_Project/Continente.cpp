#include "Continente.h"
#include "Interface.h"
#include <sstream>


//Inicializar os contadores
int Continente::nContinentes = 0;
int Planicie::nPlanicies = 0;		
int Montanha::nMontanhas = 0;
int Fortaleza::nFortalezas = 0;
int Mina::nMinas = 0;
int Duna::nDunas = 0;
int Castelo::nCastelos = 0;


Continente::Continente() {
	nContinentes++;
	Continente::setPVitoria(1);
	Continente::setCriacaoOuro(0);
	Continente::setCriacaoProduto(0);
}

Planicie::Planicie() {
	nPlanicies++;
	string name = "planicie" + to_string(nPlanicies);
	Planicie::setNome(name);
	Planicie::setResistencia(5);
	if (Interface::getAno() == 1) {
		Planicie::setCriacaoProduto(1);
		Planicie::setCriacaoOuro(1);
	} else {
		Planicie::setCriacaoProduto(2);
		Planicie::setCriacaoOuro(1);
	}
}

void Planicie::changeProductionStats() {
	if(Interface::getAno() == 2) {
		setCriacaoOuro(2);
		setCriacaoProduto(1);
	}
}
 
Montanha::Montanha() {
	nMontanhas++;
	string name = "montanha" + to_string(nMontanhas);
	Montanha::setNome(name);
	Montanha::setResistencia(6);
	Montanha::setCriacaoProduto(0);
	Montanha::setCriacaoOuro(0);
}

void Montanha::changeProductionStats() {
	turnoConquistado++;
	if(getTurnoConquistado() < 3) {		//2 primeiros turnos nao produz nada
		Montanha::setCriacaoProduto(0);
		Montanha::setCriacaoOuro(0);
	} else
		Montanha::setCriacaoProduto(1);
}

Fortaleza::Fortaleza() {
	nFortalezas++;
	string name = "fortaleza" + to_string(nFortalezas);
	Fortaleza::setNome(name);
	Fortaleza::setResistencia(8);
	Fortaleza::setCriacaoOuro(0);
	Fortaleza::setCriacaoProduto(0);
}

Mina::Mina() {
	nMinas++;
	string name = "mina" + to_string(nMinas);
	Mina::setNome(name);
	Mina::setResistencia(5);
}

void Mina::changeProductionStats() {
	if(Interface::getTurnos() < 3)
		Mina::setCriacaoOuro(1);
	else
		Mina::setCriacaoOuro(2);
}

Duna::Duna() {
	nDunas++;
	string name = "duna" + to_string(nDunas);
	Duna::setNome(name);
	Duna::setResistencia(4);
	Duna::setCriacaoProduto(1);
	Duna::setCriacaoOuro(0);
}

Castelo::Castelo() {
	nCastelos++;
	string name = "castelo" + to_string(nCastelos);
	Castelo::setNome(name);
	Castelo::setResistencia(7);
	Castelo::setCriacaoOuro(1);
}

void Castelo::changeProductionStats() {
	if(Interface::getTurnos() < 2)
		Castelo::setCriacaoProduto(3);
	else
		Castelo::setCriacaoProduto(0);
}