#include <vector>
#include <sstream>
#include <fstream>
#include "Mundo.h"

void Mundo::criaTerritorio(string type, int quant) {
    for(int i = 0; i < quant; i++) {
        territorios.push_back(new Territorio(type));
    }
}

void Mundo::configurarMundo() {
    criaTerritorio("Territorio", 10);
    criaTerritorio("Territorio", 5);
}

string Mundo::getAsString() const {
    ostringstream os;

    for(auto it = territorios.begin(); it < territorios.end(); it++)
        os << (*it)->getNome() << " ";

    return os.str();
}

void Mundo::parseComando() {
}