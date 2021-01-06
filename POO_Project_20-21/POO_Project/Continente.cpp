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


Continente::Continente()
{
	nContinentes++;
	string name = "Continente" + to_string(nContinentes);
	Continente::setNome(name);
	Continente::setPVitoria(1);
	Continente::setCriacaoOuro(0);
	Continente::setCriacaoProduto(0);
}

Planicie::Planicie()
{
	nPlanicies++;
	string name = "Planicie" + to_string(nPlanicies);
	Planicie::setNome(name);
	Planicie::setResistencia(5);
	if (Interface::getTurnos() < 6) {
		Planicie::setCriacaoProduto(1);
		Planicie::setCriacaoOuro(1);
	}
	else {
		Planicie::setCriacaoProduto(2);
		Planicie::setCriacaoOuro(1);
	}
}

Montanha::Montanha()
{
	nMontanhas++;
	string name = "Montanha" + to_string(nMontanhas);
	Montanha::setNome(name);
	Montanha::setResistencia(6);
	if (turnosConquistado < 3) {		//2 primeiros turnos nao produz nada
		Montanha::setCriacaoProduto(0);
		Montanha::setCriacaoOuro(0);
	}
	else {
		Montanha::setCriacaoProduto(1);
		Montanha::setCriacaoOuro(0);
	}
}

Fortaleza::Fortaleza()
{
	nFortalezas++;
	string name = "Fortaleza" + to_string(nFortalezas);
	Fortaleza::setNome(name);
	Fortaleza::setResistencia(8);
	Fortaleza::setCriacaoOuro(0);
	Fortaleza::setCriacaoProduto(0);
}

Mina::Mina()
{
	nMinas++;
	string name = "Mina" + to_string(nMinas);
	Mina::setNome(name);
	Mina::setResistencia(5);
	if (Interface::getTurnos() < 3 || (Interface::getTurnos() > 5 && Interface::getTurnos() < 9)) {
		Mina::setCriacaoOuro(1);
	}
	else {
		Mina::setCriacaoOuro(2);
	}
}

Duna::Duna()
{
	nDunas++;
	string name = "Duna" + to_string(nDunas);
	Duna::setNome(name);
	Duna::setResistencia(4);
	Duna::setCriacaoProduto(1);
	
}

Castelo::Castelo()
{
	nCastelos++;
	string name = "Castelo" + to_string(nCastelos);
	Castelo::setNome(name);
	Castelo::setResistencia(7);
	Castelo::setCriacaoOuro(1);
	if (Interface::getTurnos() < 2 || (Interface::getTurnos() > 5 && Interface::getTurnos() < 8)) {
		Castelo::setCriacaoProduto(3);
	}
	else {
		Castelo::setCriacaoProduto(0);
	}
}
