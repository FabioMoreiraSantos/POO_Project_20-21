#include "Interface.h"

int Interface::turno = 0;
void toLowerCase(string& word);

void Interface::run() {
    string command;

    while(true) {
        o_stream << "[" << getFaseName() << "] Commando: ";
        getline(i_stream, command);


        if(command.size() == 0)
            continue;

        toLowerCase(command);

        parseCommand(command);
    }
}

void toLowerCase(string &word) {
    for (int i = 0; i < word.size(); i++)
        word[i] = tolower(word[i]);
}

void Interface::parseCommand(string command) {
    
    vector<string> commandVector;
    string commandType;
    Territorio* territorioAConquistar;
    int commandResult;
    Imperio* imperio = mundo->getImperio();

    commandVector = splitString(command);
    commandType = commandVector[0];

    if(commandType == "avanca") {
        nextFase();
    } else if(commandType == "cria" && fase == F_CONFIG){ // Cria territorios
        if(mundo->criaTerritorios(commandVector[1], stoi(commandVector[2])))
            o_stream << commandVector[1] << " criado com sucesso!" << endl;

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
        
        if(territorioAConquistar != NULL && imperio->conquistar(territorioAConquistar))
            o_stream << "Territorio [" << territorioAConquistar->getNome() << "] conquistado!!" << endl;
        else if(territorioAConquistar == NULL)
            o_stream << "Introduza uma territorio valido!!" << endl;
        else
            o_stream << "Conquista Falhada!!" << endl;
    } else if (commandType == "adquire" && commandVector.size() == 2 && fase == F_COMPRA) {
        commandResult = mundo->imperioAdquireTecnologia(commandVector[1]);

        if(commandResult == 0)
            o_stream << "[SUCCESS] Tecnologia adquirida com sucesso!" << endl;
        else if(commandResult == -1)
		    o_stream << "[ERRO] A tecnologia que pretende adquirir nao existe" << endl;
        else if(commandResult == -2)
            o_stream << "[ERRO] Nao tem dinheiro suficiente para comprar esta tecnologia" << endl;
        else if(commandResult == -3)
            o_stream << "[ERRO] Tecnologia ja foi adquirida" << endl;
    } else if(commandType == "modifica" && commandVector.size() == 3) {
        commandResult = imperio->modifica(commandVector[1], stoi(commandVector[2]));

        if(commandResult == 0)
            o_stream << "[SUCCESS] Novo valor de " << commandVector[1] << " e " << commandVector[2] << " unidades." << endl;
        else if(commandResult == -1)
            o_stream << "[ERRO] Tipo de recurso invalido. Este deve ser 'ouro' ou 'prod'." << endl;
        else if(commandResult == -2)
            o_stream << "[ERRO] A quantidade que inseriu e superior a capacidade do imperio: " << imperio->getMaxUnidades() << " unidades." << endl;
    } else if(commandType == "maisouro" && fase == F_RECOLHA) {
        commandResult = imperio->maisOuro();

        if(commandResult == 0)
            o_stream << "[SUCCESS] Troca efetuada com sucesso! Total de ouro: " << imperio->getArmazemOuro() << " unidades." << endl;
        else if(commandResult == -1)
            o_stream << "[ERRO] Falha ao efetuar troca. Nao tem produtos suficientes para trocar." << endl;
        else if(commandResult == -2)
            o_stream << "[ERRO] Impossivel efetuar troca. Ainda nao adquiriu a tecnologia Bolsa de valores." << endl;
        else if(commandResult == -3)
            o_stream << "[ERRO] Falha ao efetuar troca. Nao tem mais espaco no armazem de ouro." << endl;
    } else if(commandType == "maisprod" && fase == F_RECOLHA) {
        commandResult = imperio->maisProd();

        if(commandResult == 0)
            o_stream << "[SUCCESS] Troca efetuada com sucesso! Total de produtos: " << imperio->getArmazemProds() << " unidades." << endl;
        else if(commandResult == -1)
            o_stream << "[ERRO] Falha ao efetuar troca. Nao tem ouro suficiente para trocar." << endl;
        else if(commandResult == -2)
            o_stream << "[ERRO] Impossivel efetuar troca. Ainda nao adquiriu a tecnologia Bolsa de valores." << endl;
        else if(commandResult == -3)
            o_stream << "[ERRO] Falha ao efetuar troca. Nao tem mais espaco no armazem de produtos." << endl;
    } else if(commandType == "maismilitar" && fase == F_RECOLHA) {
        commandResult = imperio->maisMilitar();

        if(commandResult == 0)
            o_stream << "[SUCCESS] Troca efetuada com sucesso! Forca militar atual: " << imperio->getForcaMilitar() << " unidades." << endl;
        else if(commandResult == -1)
            o_stream << "[ERRO] Falha ao efetuar troca. Nao tem ouro e/ou produtos suficiente para trocar." << endl;
        else if(commandResult == -2)
            o_stream << "[ERRO] Impossivel efetuar troca. Ainda nao adquiriu a tecnologia Bolsa de valores." << endl;
        else if(commandResult == -3)
            o_stream << "[ERRO] Falha ao efetuar troca. Ja atingiu o valor de forca militar maximo." << endl;
    } else if (commandType == "passa" && fase == F_CONQUISTA) {
        nextFase();
    }
    else
        o_stream << "[ERRO] Comando invalido!" << endl;
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
    if (fase == 4) {
        fase = 1;
        turno++;
    }
    else fase++;
    if(fase == 2)
        mundo->getImperio()->recolheMaterias();
}

string Interface::getFaseName() {
    if(fase == F_CONFIG) return "CONFIGURA";
    else if (fase == F_CONQUISTA) return "CONQUISTA/PASSA";
    else if (fase == F_COMPRA) return "COMPRA";
    else if (fase == F_RECOLHA) return "RECOLHA";
    else if (fase == F_EVENTOS) return "EVENTOS";
    else return "";
}

int Interface::getTurnos()
{
    return turno;
}
