#include "Imperio.h"
#include <iterator>
#include <sstream>

Imperio::Imperio() {}

int Imperio::getMaxUnidades()
{
	return maxUnidades;
}

int Imperio::getMaxMilitar()
{
	return maxMilitar;
}

string Imperio::getVectorImperio()
{
	ostringstream oss;
	oss << "Imperio: ";

	for (Territorio t : imperio) {
		oss << t.getNome() << " ";
	}

	return oss.str();
	

}

void Imperio::setMaxUnidades(int maximo)
{
	maxUnidades = maximo;
}

void Imperio::setMaxMilitar(int max)
{
	maxMilitar = max;
}

void Imperio::addTerritorio(Territorio territorio)
{
	imperio.push_back(territorio);
}

void Imperio::removeTerritorio(Territorio territorio)
{
	vector<Territorio>::iterator it;			//Iterador do vetor do imperio
	it = imperio.begin();

	while (it != imperio.end()) {
		if (it->getNome() == territorio.getNome()) {
			it = imperio.erase(it);
			break;
		}
			
		it++;
	}
}
