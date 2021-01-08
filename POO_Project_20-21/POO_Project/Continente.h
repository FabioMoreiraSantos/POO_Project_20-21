#ifndef Continente_HEADER
#define Continente_HEADER

#include <iostream>
#include "Territorio.h"

using namespace std;

class Continente: public Territorio
{
	static int nContinentes;
public:
	Continente();
};
class Planicie: public Continente 
{
	static int nPlanicies;
public:
	Planicie();
};
class Montanha : public Continente
{
	static int nMontanhas;
	int turnosConquistado = 0;
public:
	Montanha();
};
class Fortaleza : public Continente 
{
	static int nFortalezas;
public:
	Fortaleza();
};
class Mina : public Continente
{
	static int nMinas;
public:
	Mina();
};
class Duna : public Continente
{
	static int nDunas;
public:
	Duna();
};
class Castelo : public Continente
{
	static int nCastelos;
public:
	Castelo();
};



#endif

