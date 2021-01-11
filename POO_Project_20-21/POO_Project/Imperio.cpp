#include "Imperio.h"
#include "Tecnologia.h"
#include <iterator>
#include <sstream>
#include <time.h>

#define MAX 6
#define MIN 1

// class BolsaValores;
// class MisseisTeleguiados;
// class DefesasTerritoriais;
// class DroneMilitar;
// class BancoCentral;

Imperio::Imperio(Territorio* territorioInicial) {
	addTerritorio(territorioInicial);
	territorioInicial->setIsConquistado(true);
}

Imperio::Imperio(const Imperio& ref) {
	for(auto it = ref.reinado.begin(); it < ref.reinado.end(); it++)
		reinado.push_back((*it));
	
	armazemProdutos = ref.armazemProdutos;
	armazemOuro = ref.armazemOuro;
	maxUnidades = ref.maxUnidades;
	forcaMilitar = ref.forcaMilitar;
	maxMilitar = ref.maxMilitar;
}

Imperio& Imperio::operator=(const Imperio& c) {
	if(this == &c) { return *this; }

	reinado.clear();

	for(auto it = c.reinado.begin(); it < c.reinado.end(); it++)
		reinado.push_back((*it));

	armazemProdutos = c.armazemProdutos;
	armazemOuro = c.armazemOuro;
	maxUnidades = c.maxUnidades;
	forcaMilitar = c.forcaMilitar;
	maxMilitar = c.maxMilitar;

	return *this;
}

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
void Imperio::setCanConquistarIlhas(bool val) { canConquistarIlhas = val; }
void Imperio::setCanExchangeProdutosOuro(bool val) { canExchangeProdutosOuro = val; }

void Imperio::incrementNDefesasTerritoriais() {
	nDefesasTerritoriais++;
}

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
	if(territorio->getIsConquistado()) return false;

	int fatorSorte = randomNumEntre(MAX,MIN);
	int soma = fatorSorte + forcaMilitar;

	
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
		<< "Territorios conquistados: " << reinado.size() << endl
		<< getListaTecnologias() << endl;

	return os.str();
}

string Imperio::getListaTecnologias() const {
	ostringstream os;

	os << "Tecnologias adquiridas: ";

	if(tecnologias.size() > 0)
		for(auto it = tecnologias.begin(); it < tecnologias.end(); it++) {
			os << (*it)->getNome() << " ";
		}
	else
		os << "Ainda nao foi adquirida nenhuma tecnologia" << endl;

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

int Imperio::adquirirTecnologia(string nomeTecnologia) {
	Tecnologia *newTecnologia;
	ostringstream os;

	if(nomeTecnologia == "drone_militar")
		if(DroneMilitar::custo <= armazemOuro) {
			newTecnologia = new DroneMilitar();
			setMaxMilitar(5);
			armazemOuro -= DroneMilitar::custo;
		} else return -2;
	else if(nomeTecnologia == "bolsa_de_valores")
		if(BolsaValores::custo <= armazemOuro) {
			newTecnologia = new BolsaValores();
			setCanExchangeProdutosOuro(true);
			armazemOuro -= BolsaValores::custo;
		} else return -2;
	else if(nomeTecnologia == "misseis_teleguiados")
		if(MisseisTeleguiados::custo <= armazemOuro) {
			newTecnologia = new MisseisTeleguiados();
			setCanConquistarIlhas(true);
			armazemOuro -= MisseisTeleguiados::custo;
		} else return -2;
	else if(nomeTecnologia == "defesas_territoriais")
		if(DefesasTerritoriais::custo <= armazemOuro) {
			newTecnologia = new DefesasTerritoriais();
			incrementNDefesasTerritoriais();
			armazemOuro -= DefesasTerritoriais::custo;
		} else return -2;
	else if(nomeTecnologia == "banco_central")
		if(BancoCentral::custo <= armazemOuro) {
			newTecnologia = new BancoCentral();
			setMaxUnidades(5);
			armazemOuro -= BancoCentral::custo;
		} else return -2;
	else {
		return -1;
	}
	
	tecnologias.push_back(newTecnologia);

	// for(auto it = tecnologias.begin(); it < tecnologias.end(); it++) {
	// 	cout << " " << (*it)->getNome();
	// 	// (*it)->print();
	// };
	// cout << endl;

	return 0;
}
