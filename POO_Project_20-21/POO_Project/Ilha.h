#ifndef Ilha_HEADER
#define Ilha_HEADER

#include <iostream>
#include "Territorio.h"

class Ilha: public Territorio
{
	static int nIlhas;
	bool acessivel = false;
public:
	Ilha();
};


class RefugioPiratas: public Ilha
{
	static int nRefugiosPiratas;
public:
	RefugioPiratas();
};

class Pescaria : public Ilha
{
	static int nPescarias;
public:
	Pescaria();
};

#endif

