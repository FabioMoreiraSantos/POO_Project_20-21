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

// Lista info do imperio
string Mundo::lista() const {
    ostringstream os;

    os << imperio->listaInfo();

    return os.str();
}

// Lista info dos terrtorios
string Mundo::lista(const string nomeTerritorio) const {
    ostringstream os;

    if (nomeTerritorio == "conquistados")
        os << imperio->listaConquistados();
    else
        for(auto it = territorios.begin(); it < territorios.end(); it++) {
            // Mostra lista de territorios
            if(nomeTerritorio == "territorios")
                os << (*it)->getNome() << " ";
            
            // Mostra info de um territorio
            else if((*it)->getNome() == nomeTerritorio)
                os << (*it)->listaInfo();
        }

    return os.str();
}

Territorio* Mundo::getTerritorioByName(string territorioName) {
    for(auto it = territorios.begin(); it < territorios.end(); it++)
        if((*it)->getNome() == territorioName)
            return (*it);

    return NULL;
}
