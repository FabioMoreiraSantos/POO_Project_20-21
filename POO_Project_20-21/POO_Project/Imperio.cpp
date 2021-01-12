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
	
	for(auto it = ref.tecnologias.begin(); it < ref.tecnologias.end(); it++)
		tecnologias.push_back((*it));

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

int Imperio::getReinadoSize()
{
	return reinado.size();
}

void Imperio::setMaxUnidades(int maximo) { maxUnidades = maximo; }
void Imperio::setMaxMilitar(int max) { maxMilitar = max; }
void Imperio::setCanConquistarIlhas(bool val) { canConquistarIlhas = val; }
void Imperio::setCanExchangeProdutosOuro(bool val) { canExchangeProdutosOuro = val; }

void Imperio::incrementNDefesasTerritoriais() {
	nDefesasTerritoriais++;
}

void Imperio::setArmazemProdutos(int produtos)
{
	armazemProdutos += produtos;
}
void Imperio::setArmazemOuro(int ouro)
{
	armazemOuro += ouro;
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

void Imperio::recolheMaterias()
{
	//Percorre o vetor de territorios conquistados e incrementa os 
	//valores de ouro e produtos ao seu armazem
	for (auto it = reinado.begin(); it < reinado.end(); it++) {
		// Incrementa as materias primas
		setArmazemOuro((*it)->getCriacaoOuro());
		setArmazemProdutos((*it)->getCriacaoProduto());
	}
}

int randomNumEntre(int max, int min) {
	return (rand() % (MAX - MIN + 1) + MIN);
}

bool Imperio::conquistar(Territorio * territorio) {
	if(territorio->getIsConquistado()) return false;

	int fatorSorte = randomNumEntre(MAX,MIN);
	int soma = fatorSorte + forcaMilitar;
	cout << "Fator Sorte: " << fatorSorte << endl;
	cout << "Forca militar: " << forcaMilitar << endl;
	cout << "Total: " << soma << endl;
	cout << "Resistencia de " << territorio->getNome() 
		<< " " << territorio->getResistencia() << endl;

	if (soma >= territorio->getResistencia()) {
		this->addTerritorio(territorio);
		territorio->setIsConquistado(true);
		return true;
	}
	else {
		if (forcaMilitar > 0)
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
	else if(nomeTecnologia == "bolsa_de_valores") {
		if(hasTecnologiaByName("BolsaValores"))
			return -3;
		if(BolsaValores::custo <= armazemOuro) {
			newTecnologia = new BolsaValores();
			setCanExchangeProdutosOuro(true);
			armazemOuro -= BolsaValores::custo;
		} else return -2;
	} else if(nomeTecnologia == "misseis_teleguiados")
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
	else if(nomeTecnologia == "banco_central") {
		if(hasTecnologiaByName("BancoCentral"))
			return -3;

		if(BancoCentral::custo <= armazemOuro) {
			newTecnologia = new BancoCentral();
			setMaxUnidades(5);
			armazemOuro -= BancoCentral::custo;
		} else return -2;
	} else
		return -1;
	
	tecnologias.push_back(newTecnologia);

	return 0;
}

bool Imperio::hasTecnologiaByName(string nameTecnologia) const {
	for(auto it = tecnologias.begin(); it < tecnologias.end(); it++)
		if((*it)->getNome() == nameTecnologia)
			return true;
	
	return false;
}

int Imperio::modifica(string type, int quant) {
	if(maxUnidades >= quant)
		if(type == "ouro")
			armazemOuro = quant;
		else if(type == "prod")
			armazemProdutos = quant;
		else
			return -1;
	else
		return -2;

	return 0;
}

int Imperio::maisOuro() {
	if(canExchangeProdutosOuro) {
		if(armazemProdutos >= 2)
			if(armazemOuro < maxUnidades) {
				armazemOuro++;
				armazemProdutos -= 2;
			} else
				return -3; // Exceeded maxUnidades
		else
			return -1; // Not enough products
	} else
		return -2; // Needs to buy bolsa de valores

	return 0;
}

int Imperio::maisProd() {
	if(canExchangeProdutosOuro) {
		if(armazemOuro >= 2)
			if(armazemProdutos < maxUnidades) {
				armazemProdutos++;
				armazemOuro -= 2;
			} else
				return -3; // Exceeded maxUnidades
		else
			return -1; // Not enough ouro
	} else
		return -2; // Needs to buy bolsa de valores

	return 0;
}

int Imperio::maisMilitar() {
	if(canExchangeProdutosOuro) {
		if(armazemOuro >= 1 && armazemProdutos >= 1)
			if(forcaMilitar < maxMilitar) {
				forcaMilitar++;
				armazemOuro--;
				armazemProdutos--;
			} else
				return -3; // Exceeded maxMilitar
		else
			return -1; // Not enough products and ouro
	} else
		return -2; // Needs to buy bolsa de valores

	return 0;
}

int Imperio::takeTerritorio(Territorio* territorio) {
	if(territorio->getIsConquistado()) return -1;

	this->addTerritorio(territorio);
	territorio->setIsConquistado(true);

	return 0;
}

int Imperio::takeTecnologia(string nameTecnologia) {
	Tecnologia *newTecnologia;
	ostringstream os;

	if(nameTecnologia == "drone_militar") {
		newTecnologia = new DroneMilitar();
		setMaxMilitar(5);
	} else if(nameTecnologia == "bolsa_de_valores") {
		if(hasTecnologiaByName("BolsaValores"))
			return -2;
		newTecnologia = new BolsaValores();
		setCanExchangeProdutosOuro(true);
	} else if(nameTecnologia == "misseis_teleguiados") {
		newTecnologia = new MisseisTeleguiados();
		setCanConquistarIlhas(true);
	} else if(nameTecnologia == "defesas_territoriais") {
		newTecnologia = new DefesasTerritoriais();
		incrementNDefesasTerritoriais();
	} else if(nameTecnologia == "banco_central") {
		if(hasTecnologiaByName("BancoCentral"))
			return -2;
		newTecnologia = new BancoCentral();
		setMaxUnidades(5);
	} else
		return -1;
	
	tecnologias.push_back(newTecnologia);

	return 0;
}

