#include "Imperio.h"

int Imperio::getMaxUnidades() {
	return maxUnidades;
}

int Imperio::getMaxMilitar() {
	return maxMilitar;
}

void Imperio::setMaxUnidades(int maximo) {
	maxUnidades = maximo;
}

void Imperio::setMaxMilitar(int max) {
	maxMilitar = max;
}

string Imperio::listaInfo() const {
	ostringstream os;
	os << "Armazem Produtos: " << armazemProdutos << "/" << maxUnidades << endl
		<< "Armazem Ouro: " << armazemOuro << "/" << maxUnidades << endl
		<< "Forca Militar: " << forcaMilitar << "/" << maxMilitar << endl
		<< "Territorios conquistados: " << 12 << endl;

	return os.str();
}