#include "Imperio.h"
#include <iterator>
#include <sstream>
#include <time.h>

#define MAX 6
#define MIN 1

int Imperio::getMaxUnidades() { return maxUnidades; }
int Imperio::getMaxMilitar() { return maxMilitar; }

string Imperio::getVectorImperio() {
	ostringstream oss;
	oss << "Imperio: ";

	for (Territorio *t : reinado) {
		oss << t->getNome() << " ";
	}

	return oss.str();
}

void Imperio::setMaxUnidades(int maximo) { maxUnidades = maximo; }
void Imperio::setMaxMilitar(int max) { maxMilitar = max; }
void Imperio::addTerritorio(Territorio * territorio) { reinado.push_back(territorio); }

void Imperio::removeTerritorio(Territorio * territorio) {
	vector<Territorio *>::iterator it;			//Iterador do vetor do imperio
	it = reinado.begin();

	while (it != reinado.end()) {
		if ((*it)->getNome() == territorio->getNome()) {
			it = reinado.erase(it);
			break;
		}
		
		it++;
	}
}

int randomNumEntre(int max, int min) {
	return (rand() % (MAX - MIN + 1) + MIN);
}

bool Imperio::conquistar(Territorio * territorio) {
	int fatorSorte = randomNumEntre(MAX,MIN);
	int soma = fatorSorte + forcaMilitar;
	cout << soma << endl;

	if (soma >= territorio->getResistencia()) {
		this->addTerritorio(territorio);
		territorio->setIsConquistado(true);
		return true;
	}
	else {
		territorio->setIsConquistado(true);
		if(forcaMilitar != 0)
			forcaMilitar--;
		return false;
	}
}

string Imperio::listaInfo() const {
	ostringstream os;
	os << "Armazem Produtos: " << armazemProdutos << "/" << maxUnidades << endl
		<< "Armazem Ouro: " << armazemOuro << "/" << maxUnidades << endl
		<< "Forca Militar: " << forcaMilitar << "/" << maxMilitar << endl
		<< "Territorios conquistados: " << reinado.size() << endl;

	return os.str();
}

string Imperio::listaConquistados() const {
	ostringstream os;

	if(reinado.size() > 0)
		for(auto it = reinado.begin(); it < reinado.end(); it++) {
			os << (*it)->getNome() << " ";
		}
	else
		os << "Ainda nao foi conquistado nenhum territorio" << endl;

	return os.str();
}

