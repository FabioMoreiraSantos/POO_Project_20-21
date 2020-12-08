#include "Interface.h"

void Interface::run() {
    string command;

    while(true) {
        o_stream << "[" << getFaseName() << "] Commando: ";
        getline(i_stream, command);

        if(command.size() == 0)
            continue;

        parseCommand(command);
    }
}

void Interface::parseCommand(string command) {
    vector<string> commandVector;
    string commandType;
    Territorio* territorioAConquistar;

    commandVector = splitString(command);
    commandType = commandVector[0];

    if(commandType == "avanca") {
        nextFase();
    } else if(commandType == "cria" && fase == F_CONFIG){ // Cria territorios
        if(mundo->criaTerritorios(commandVector[1], stoi(commandVector[2])))
            o_stream << "Territorio criado com sucesso!" << endl;

    } else if(commandType == "carrega" && fase == F_CONFIG) { // Carrega ficheiro de comandos
        if(!readFromFile(commandVector[1]))
            o_stream << "[ERRO] Ficheiro invalido!" << endl;
        else
            o_stream << "Ficheiro lido com sucesso!" << endl;

    } else if (commandType == "lista") { // Lista info
        // lista -> Lista info do imperio
        if(commandVector.size() == 1)
            o_stream << mundo->lista() << endl;

        // lista conquistados -> Lista os territorios conquistados pelo imperio
        // lista <nome_do_territorio> -> Lista info do dado territorio
        // lista <tipo_de_territorio> -> Lista os territorios do tipo dado
        else
            o_stream << mundo->lista(commandVector[1]) << endl;

    } else if (commandType == "conquista" && fase == F_CONQUISTA) {
        territorioAConquistar = mundo->getTerritorioByName(commandVector[1]);
        if(mundo->getImperio()->conquistar(territorioAConquistar))
            o_stream << "Territorio [" << territorioAConquistar->getNome() << "] conquistado!!" << endl;
        else
            o_stream << "Conquista Falhada!!" << endl;
            
    } else
        o_stream << "[ERRO] Commando invalido!" << endl;
}

bool Interface::readFromFile(string filename) {
	ifstream myfile;
    string command;

	myfile.open(filename);

    if(!myfile.fail())
        // Le e processa comando do ficheiro
        while(getline(myfile, command)) { 
            o_stream << endl << "[ Comando lido ]: " << command << endl;
            parseCommand(command);
        }
    else
        return false;

	myfile.close();

    return true;
}

// Separa uma frase num vetor de palavras
vector<string> Interface::splitString(string str) const {
    string tmp; 
    stringstream ss(str);
    vector<string> words;

    while(getline(ss, tmp, ' ')){
        words.push_back(tmp);
    }

    return words;
}

void Interface::nextFase() {
    if(fase == 4)
        fase = 1;
    else fase++;
}

string Interface::getFaseName() {
    if(fase == F_CONFIG) return "CONFIGURA";
    else if (fase == F_CONQUISTA) return "CONQUISTA/PASSA";
    else if (fase == F_COMPRA) return "COMPRA";
    else if (fase == F_RECOLHA) return "RECOLHA";
    else if (fase == F_EVENTOS) return "EVENTOS";
    else return "";
}