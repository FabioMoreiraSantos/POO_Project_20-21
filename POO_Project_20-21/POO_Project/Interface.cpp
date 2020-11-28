#include "Interface.h"

void Interface::criarMundo() {
    string command;
    do {
        // stream >> command;
        o_stream << "Commando: ";
        getline(i_stream, command);
        if(!parseCommand(command))
            break;

    } while(true);

    // o_stream << "Output => " << command << endl;
}

bool Interface::parseCommand(string command) {
    vector<string> commandVector;
    string commandType;

    commandVector = splitString(command);
    commandType = commandVector[0];

    if(commandType == "criar") {
        mundo->criaTerritorio(commandVector[1], stoi(commandVector[2]));
    } else if(commandType == "carregar") {
        readFromFile(commandVector[1]);
    } else if(commandType == "sair")
        return false;
        
    o_stream << mundo->getAsString() << endl;

    return true;
}

bool Interface::readFromFile(string filename) {
	ifstream myfile;
    string command;

	myfile.open (filename);
    while(getline(myfile, command)) {
        o_stream << command << endl;
        parseCommand(command);
    }
    


	// myfile >> "Writing this to a file.\n";
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