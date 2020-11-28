#include "Interface.h"

void Interface::criarMundo() {
    string command;
    
    do {
        o_stream << "Commando: ";
        getline(i_stream, command);
        if(command.size() == 0)
            continue;
        else if(command == "sair")
            break;
        else if(!parseCommand(command))
            o_stream << "[ERRO] Commando invalido!" << endl;

    } while(true);
}

bool Interface::parseCommand(string command) {
    vector<string> commandVector;
    string commandType;

    commandVector = splitString(command);
    commandType = commandVector[0];

    if(commandType == "cria") {
        if(mundo->criaTerritorios(commandVector[1], stoi(commandVector[2])))
            o_stream << "Territorio criado com sucesso!" << endl;
    } else if(commandType == "carrega") {
        if(!readFromFile(commandVector[1]))
            o_stream << "[ERRO] Ficheiro invalido!" << endl;
        else
            o_stream << "Ficheiro lido com sucesso!" << endl;
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