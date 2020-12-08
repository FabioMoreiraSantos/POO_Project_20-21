#include <vector>
#include <sstream>
#include <fstream>
#include "Mundo.h"

Mundo::Mundo() {
    // Territorio inicial
    criaTerritorios("Territorio", 1);
    imperio = new Imperio(territorios[0]);
}

Mundo::Mundo(const Mundo& ref) {
    for(auto it = ref.territorios.begin(); it < ref.territorios.end(); it++)
        territorios.push_back(new Territorio(*(*it)));

    imperio = new Imperio(*(ref.imperio));
}

Mundo::~Mundo() {
    // Free allocated territorios' memory
    for(auto it = territorios.begin(); it < territorios.end(); it++)
        delete (*it);
    
    delete imperio;
}

Mundo& Mundo::operator=(const Mundo& c) {
    if(this == &c) { return *this; }

    for(auto it = territorios.begin(); it < territorios.end(); it++)
        delete (*it);

    delete imperio;

    territorios.clear();

    for(auto it = c.territorios.begin(); it < c.territorios.end(); it++)
        territorios.push_back(new Territorio(*(*it)));

    imperio = new Imperio(*(c.imperio));

    return *this;
}

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
