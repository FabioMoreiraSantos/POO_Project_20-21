#include <vector>
#include <sstream>
#include <fstream>
#include "Mundo.h"

bool Mundo::criaTerritorios(string type, int quant) {
    if(type == "territorio" || type == "Territorio") {
        for(int i = 0; i < quant; i++)
            territorios.push_back(new Territorio());
    } else 
        return false;
    
    return true;
}

string Mundo::getAsString() const {
    ostringstream os;

    for(auto it = territorios.begin(); it < territorios.end(); it++)
        os << (*it)->getNome() << " ";

    return os.str();
}

string Mundo::lista() const {
    ostringstream os;

    os << imperio->listaInfo();

    return os.str();
}

string Mundo::lista(const string nomeTerritorio) const {
    ostringstream os;

    for(auto it = territorios.begin(); it < territorios.end(); it++) {
        if(nomeTerritorio == "territorios")
            os << (*it)->getNome() << " ";
        else if((*it)->getNome() == nomeTerritorio)
            os << (*it)->listaInfo();
    }

    return os.str();
}
