#include "Interface.h"

void Interface::criarMundo(istream& stream, ostream& o_stream) {
    string command;
    do {
        // stream >> command;
        o_stream << "Commando: ";
        getline(stream, command);
        if(!parseCommand(command, o_stream))
            break;

    } while(true);

    o_stream << "Output => " << command << endl;
}

bool Interface::parseCommand(string command, ostream& o_stream) const {
    vector<string> commandVector;
    string commandType;

    commandVector = splitString(command);
    commandType = commandVector[0];

    if(commandType == "criar") {
        o_stream << "CRIAR MUNDO" << endl;
    } else if(commandType == "carregar") {
        o_stream << "CARREGAR FICHEIRO" << endl;
    } else if(commandType == "sair")
        return false;

    return true;
}

vector<string> Interface::splitString(string str) const {
    string tmp; 
    stringstream ss(str);
    vector<string> words;

    while(getline(ss, tmp, ',')){
        words.push_back(tmp);
    }

    return words;
}