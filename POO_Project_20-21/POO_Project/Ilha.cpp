#include "Ilha.h"
#include "Imperio.h"
#include "Interface.h"

//Inicializar contadores de Ilhas
int Ilha::nIlhas = 0;
int RefugioPiratas::nRefugiosPiratas = 0;
int Pescaria::nPescarias = 0;

Ilha::Ilha()
{
	nIlhas++;
	string name = "ilha" + to_string(nIlhas);
	Ilha::setNome(name);
	Ilha::setCriacaoOuro(0);
	Ilha::setCriacaoProduto(0);
	Ilha::setPVitoria(2);
}

RefugioPiratas::RefugioPiratas()
{
	nRefugiosPiratas++;
	string name = "refugio_de_piratas" + to_string(nRefugiosPiratas);
	RefugioPiratas::setNome(name);
	RefugioPiratas::setResistencia(9);
	RefugioPiratas::setCriacaoOuro(1);
}

Pescaria::Pescaria()
{
	nPescarias++;
	string name = "pescaria" + to_string(nPescarias);
	Pescaria::setNome(name);
	Pescaria::setResistencia(9);
	if (Interface::getTurnos() < 6) {
		Pescaria::setCriacaoProduto(2);
	}
	else {
		Pescaria::setCriacaoProduto(4);
	}
}
