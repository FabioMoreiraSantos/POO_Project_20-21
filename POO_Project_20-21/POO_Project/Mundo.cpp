#include <vector>
#include <sstream>
#include <fstream>
#include "Mundo.h"
#include "Tecnologia.h"

Mundo::Mundo() {
    // Territorio inicial
    criaTerritorios("territorio", 1);
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
    if(type == "territorio") {
        for(int i = 0; i < quant; i++)
            territorios.push_back(new Territorio());
    }
    else if(type == "planicie") {
        for (int i = 0; i < quant; i++)
            territorios.push_back(new Planicie());
    }
    else if (type == "montanha") {
        for (int i = 0; i < quant; i++)
            territorios.push_back(new Montanha());
    }
    else if (type == "fortaleza") {
        for (int i = 0; i < quant; i++)
            territorios.push_back(new Fortaleza());
    }
    else if (type == "mina") {
        for (int i = 0; i < quant; i++)
            territorios.push_back(new Mina());
    }
    else if (type == "duna") {
        for (int i = 0; i < quant; i++)
            territorios.push_back(new Duna());
    }
    else if (type == "castelo") {
        for (int i = 0; i < quant; i++)
            territorios.push_back(new Castelo());
    }
    else if (type == "refugio_de_piratas") {
        for (int i = 0; i < quant; i++)
            territorios.push_back(new RefugioPiratas());
    }
    else if (type == "pescaria") {
        for (int i = 0; i < quant; i++)
            territorios.push_back(new Pescaria());
    }
    else {
        return false;
    }

    return true;
}

string Mundo::getAsString() const {
    ostringstream os;

    os << imperio->listaInfo() << endl;
    os << imperio->listaConquistados() << endl;
    os << imperio->getListaTecnologias() << endl;

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
string Mundo::lista(const string nome) const {
    ostringstream os;

    if (nome == "conquistados")
        os << imperio->listaConquistados();
    else if (nome == "tecnologias") {
        cout << "drone_militar: " << endl
            << "\tCusto: " << DroneMilitar::custo << " ouro " << endl
            << "\tResumo: " << DroneMilitar::descricao << endl
            << "\tAdquirida: ";
        if (imperio->hasTecnologiaByName("DroneMilitar"))
            cout << "SIM";
        else
            cout << "NAO";
        cout << "\nmisseis_teleguiados: " << endl
            << "\tCusto: " << MisseisTeleguiados::custo << " ouro " << endl
            << "\tResumo: " << MisseisTeleguiados::descricao << endl
            << "\tAdquirida: ";        
        if (imperio->hasTecnologiaByName("MisseisTeleguiados"))
            cout << "SIM";
        else
            cout << "NAO";
        cout << "\n\ndefesas_territoriais: " << endl
            << "\tCusto: " << DefesasTerritoriais::custo << " ouro " << endl
            << "\tResumo: " << DefesasTerritoriais::descricao << endl
            << "\tAdquirida: ";           
        if (imperio->hasTecnologiaByName("DefesasTerritoriais"))
            cout << "SIM";
        else
            cout << "NAO";
        cout << "\nbolsa_de_valores: " << endl
            << "\tCusto: " << BolsaValores::custo << " ouro " << endl
            << "\tResumo: " << BolsaValores::descricao << endl
            << "\tAdquirida: ";   
        if (imperio->hasTecnologiaByName("BolsaValores"))
            cout << "SIM";
        else
            cout << "NAO";
        cout << "\nbanco_central: " << endl
            << "\tCusto: " << BancoCentral::custo << " ouro " << endl
            << "\tResumo: " << BancoCentral::descricao << endl
            << "\tAdquirida: ";   
        if (imperio->hasTecnologiaByName("BancoCentral"))
            cout << "SIM";
        else
            cout << "NAO";
    }
    else
        for(auto it = territorios.begin(); it < territorios.end(); it++) {
            // Mostra lista de territorios
            if(nome == "territorios")
                os << (*it)->getNome() << " ";
            
            // Mostra info de um territorio
            else if((*it)->getNome() == nome)
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

// TODO: Verificar este caso com o stor
int Mundo::imperioAdquireTecnologia(string nomeTecnologia) {
    return imperio->adquirirTecnologia(nomeTecnologia);
}

int Mundo::tomaCommand(string type, string name) {
    Territorio* territorioAConquistar;
    if(type == "terr") {
        territorioAConquistar = getTerritorioByName(name);
        if (territorioAConquistar != NULL)
            return imperio->takeTerritorio(territorioAConquistar);
        else
            return -2;
    } else if(type == "tec") {
        return imperio->takeTecnologia(name);
    } else
        return -4;
}