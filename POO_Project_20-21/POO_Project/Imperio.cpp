#include "Imperio.h"
#include "Tecnologia.h"
#include "Interface.h"
#include <iterator>
#include <sstream>
#include <time.h>
#include <random>

#define MAX 6
#define MIN 1

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
	
	for(auto it = c.tecnologias.begin(); it < c.tecnologias.end(); it++)
		tecnologias.push_back((*it));

	armazemProdutos = c.armazemProdutos;
	armazemOuro = c.armazemOuro;
	maxUnidades = c.maxUnidades;
	forcaMilitar = c.forcaMilitar;
	maxMilitar = c.maxMilitar;

	return *this;
}

Imperio::~Imperio() {
	for(auto it = tecnologias.begin(); it < tecnologias.end(); it++)
		delete (*it);
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

void Imperio::setArmazemProdutos(int produtos) {
	armazemProdutos = produtos;
}

void Imperio::setArmazemOuro(int ouro) {
	armazemOuro = ouro;
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

void Imperio::recolheMaterias(ostream& o_stream) {
	int totalOuro = 0, totalProd = 0;
	//Percorre o vetor de territorios conquistados e incrementa os 
	//valores de ouro e produtos ao seu armazem
	for (auto it = reinado.begin(); it < reinado.end(); it++) {
		// Incrementa as materias primas
		totalOuro += (*it)->getCriacaoOuro();
		addOuro((*it)->getCriacaoOuro());
		totalProd += (*it)->getCriacaoProduto();
		addProds((*it)->getCriacaoProduto());
	}

	o_stream << "[ RECOLHA ] Recolha conluida. Recolheu " << totalOuro << " unidades de ouro e " << totalProd << " unidades de produtos." << endl;
}

int randomNumEntre(int max, int min) {
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> distr(min, max); // define the range

    return distr(gen);
}

int Imperio::conquistar(Territorio * territorio, ostream& o_stream) {
	if(territorio->getIsConquistado()) return false;

	int fatorSorte = randomNumEntre(MAX,MIN);
	int soma = fatorSorte + forcaMilitar;
	o_stream << "Fator Sorte: " << fatorSorte << endl
	<< "Forca militar: " << forcaMilitar << endl
	<< "Total: " << soma << endl
	<< "Resistencia de " << territorio->getNome() 
		<< ": " << territorio->getResistencia() << endl;

	if((territorio->isA<Ilha>() && !canConquistarIlhas && getReinadoSize() < 5) == true)
		return -2;

	
	if (soma >= territorio->getResistencia()) {
		this->addTerritorio(territorio);
		territorio->setIsConquistado(true);
		return 0;
	} else {
		if (forcaMilitar > 0)
			forcaMilitar--;
		return -1;
	}
}

string Imperio::listaInfo() const {
	ostringstream os;
	os << "Armazem Produtos: " << armazemProdutos << "/" << maxUnidades << endl
		<< "Armazem Ouro: " << armazemOuro << "/" << maxUnidades << endl
		<< "Forca Militar: " << forcaMilitar << "/" << maxMilitar << endl
		<< "Producao de ouro: " << getOuroProduction() << endl
		<< "Producao de produtos: " << getProdProduction() << endl
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
			os << (*it)->getNome() << endl
				<< "\tResistencia: " << (*it)->getResistencia() << endl
				<< "\tCriacao de Ouro: " << (*it)->getCriacaoOuro() << endl
				<< "\tCriacao de Produtos:" << (*it)->getCriacaoProduto() << endl;
		}
	else
		os << "Ainda nao foi conquistado nenhum territorio" << endl;

	return os.str();
}

/*
	0 - success
	-1 - name invalid
	-2 - armazem not full
	-3 - já existe tecnologia no imperio
*/
int Imperio::adquirirTecnologia(string nomeTecnologia) {
	Tecnologia *newTecnologia;
	ostringstream os;

	if(nomeTecnologia == "drone_militar") {
		if(hasTecnologiaByName("DroneMilitar"))
			return -3;

		if(DroneMilitar::custo <= armazemOuro) {
			newTecnologia = new DroneMilitar();
			setMaxMilitar(5);
			armazemOuro -= DroneMilitar::custo;
		} else return -2;
	} else if(nomeTecnologia == "bolsa_de_valores") {
		if(hasTecnologiaByName("BolsaValores"))
			return -3;
		if(BolsaValores::custo <= armazemOuro) {
			newTecnologia = new BolsaValores();
			setCanExchangeProdutosOuro(true);
			armazemOuro -= BolsaValores::custo;
		} else return -2;
	} else if(nomeTecnologia == "misseis_teleguiados") {
		if(hasTecnologiaByName("MisseisTeleguiados"))
			return -3;
		if(MisseisTeleguiados::custo <= armazemOuro) {
			newTecnologia = new MisseisTeleguiados();
			setCanConquistarIlhas(true);
			armazemOuro -= MisseisTeleguiados::custo;
		} else return -2;
	} else if(nomeTecnologia == "defesas_territoriais") {
		if(hasTecnologiaByName("DefesasTerritoriais"))
			return -3;
		if(DefesasTerritoriais::custo <= armazemOuro) {
			newTecnologia = new DefesasTerritoriais();
			incrementNDefesasTerritoriais();
			armazemOuro -= DefesasTerritoriais::custo;
		} else return -2;
	} else if(nomeTecnologia == "banco_central") {
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
				incrementOuro();
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
				incrementProd();
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
		if(hasTecnologiaByName("DroneMilitar"))
			return -2;
		newTecnologia = new DroneMilitar();
		setMaxMilitar(5);
	} else if(nameTecnologia == "bolsa_de_valores") {
		if(hasTecnologiaByName("BolsaValores"))
			return -2;
		newTecnologia = new BolsaValores();
		setCanExchangeProdutosOuro(true);
	} else if(nameTecnologia == "misseis_teleguiados") {
		if(hasTecnologiaByName("MisseisTeleguiados"))
			return -2;
		newTecnologia = new MisseisTeleguiados();
		setCanConquistarIlhas(true);
	} else if(nameTecnologia == "defesas_territoriais") {
		if(hasTecnologiaByName("DefesasTerritoriais"))
			return -2;
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

void Imperio::incrementOuro(){
	if(armazemOuro < maxUnidades)	
		armazemOuro++;
}

void Imperio::incrementProd(){
	if(armazemProdutos < maxUnidades)	
		armazemProdutos++;
}

void Imperio::addOuro(int quant) {
	if(armazemOuro + quant <= maxUnidades)	
		armazemOuro += quant;
}

void Imperio::addProds(int quant) {
	if(armazemProdutos + quant <= maxUnidades)	
		armazemProdutos += quant;
}

void Imperio::incrementForcaMilitar(){
	if(forcaMilitar < maxMilitar)	
		forcaMilitar++;
}

int Imperio::sufferInvasion(int ano, ostream& o_stream) {
	int fatorSorte = randomNumEntre(6, 1);
	int forcaInvasao = fatorSorte + ano + 1;
	Territorio* territorioBeingInvaded = getLastConqueredTerritorio();
	bool isInvasionSuccessful = territorioBeingInvaded->getResistencia() + nDefesasTerritoriais < forcaInvasao;

	o_stream << "Territorio " << territorioBeingInvaded->getNome() << " invadido" << endl;
	o_stream << "Fator Sorte: " << fatorSorte << endl;
	o_stream << "Forca da Invasao: " << forcaInvasao << endl;
	o_stream << "Total: " << fatorSorte+forcaInvasao << endl;
	o_stream << "Resistencia de " << territorioBeingInvaded->getNome()
		<< " " << territorioBeingInvaded->getResistencia() << endl;


	if(isInvasionSuccessful) {
		o_stream << "[ EVENTO ] Invasao foi bem sucedida." << endl;
		territorioBeingInvaded->setIsConquistado(false);
		reinado.pop_back();

		if(reinado.size() == 0) {
			return -1; // Lose game
		}
		
	} else
		o_stream << "[ EVENTO ] Invasao falhou." << endl;;

	return 0; // Invasion successful
}

Territorio* Imperio::getLastConqueredTerritorio() {
	return reinado[reinado.size() - 1];
}

int Imperio::getOuroProduction() const {
	int total = 0;
	for(auto it = reinado.begin(); it < reinado.end(); it++)
		total += (*it)->getCriacaoOuro();

	return total;
}

int Imperio::getProdProduction() const {
	int total = 0;
	for(auto it = reinado.begin(); it < reinado.end(); it++)
		total += (*it)->getCriacaoProduto();

	return total;
}

int Imperio::getTecnologiasCount() const {
	return tecnologias.size();
}

int Imperio::getPontosVitoria() const {
	int total = 0;

	for(auto it = reinado.begin(); it < reinado.end(); it++)
		total += (*it)->getPVitoria();

	return total;
}

void Imperio::triggerTurnBasedTerrActions() {
	for(auto it = reinado.begin(); it < reinado.end(); it++) {
		if((*it)->isA<Montanha>() || (*it)->isA<Planicie>() || (*it)->isA<Castelo>() 
		|| (*it)->isA<Pescaria>() || (*it)->isA<Mina>()) {
			(*it)->changeProductionStats();
		}
	}
}