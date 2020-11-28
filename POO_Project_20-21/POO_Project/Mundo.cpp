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
