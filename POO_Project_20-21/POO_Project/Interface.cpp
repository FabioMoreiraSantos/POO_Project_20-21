#include "Interface.h"

void Interface::run() {
    string command;

    while(true) {
        o_stream << "[" << getFaseName() << "] Commando: ";
        getline(i_stream, command);

        if(command.size() == 0)
            continue;
        else if(command == "avanca") {
            nextFase();
            continue;
        } else if(!parseCommand(command))
            o_stream << "[ERRO] Commando invalido!" << endl;

    }
}

bool Interface::parseCommand(string command) {
    vector<string> commandVector;
    string commandType;

    commandVector = splitString(command);
    commandType = commandVector[0];

    if(commandType == "cria" && fase == F_CONFIG){
        if(mundo->criaTerritorios(commandVector[1], stoi(commandVector[2])))
            o_stream << "Territorio criado com sucesso!" << endl;
    } else if(commandType == "carrega" && fase == F_CONFIG) {
        if(!readFromFile(commandVector[1]))
            o_stream << "[ERRO] Ficheiro invalido!" << endl;
        else
            o_stream << "Ficheiro lido com sucesso!" << endl;
    } else if (commandType == "lista") {
        if(commandVector.size() == 1)
            o_stream << mundo->lista() << endl;
        else
            o_stream << mundo->lista(commandVector[1]) << endl;
            
    } else
        return false;
    // o_stream << mundo->getAsString() << endl;

    return true;
}

bool Interface::readFromFile(string filename) {
	ifstream myfile;
    string command;

	myfile.open(filename);

    if(!myfile.fail())
        while(getline(myfile, command)) {
            o_stream << command << endl;
            parseCommand(command);
        }
    else
        return false;

	myfile.close();

    return true;
}

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