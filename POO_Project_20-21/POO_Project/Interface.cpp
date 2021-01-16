#include "Interface.h"
#include "Tecnologia.h"

int Interface::turno = 0;
int Interface::ano = 1;
void toLowerCase(string& word);

Interface::~Interface() {
    delete mundo;

    for(auto it = savedSnapshots.begin(); it < savedSnapshots.end(); it++)
        delete *it;
}


int randNum(int min, int max){
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> distr(min, max); // define the range

    return distr(gen);
}


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

    if(commandType == "avanca")
        nextFase();
    else if(commandType == "cria" && fase == F_CONFIG) // Cria territorios
        commandCria(commandVector);
    else if(commandType == "carrega" && fase == F_CONFIG) // Carrega ficheiro de comandos
        commandCarrega(commandVector);
    else if (commandType == "lista") // Lista info
        commandLista(commandVector);
    else if (commandType == "conquista" && fase == F_CONQUISTA)
        commandConquista(commandVector);
    else if (commandType == "adquire" && fase == F_COMPRA)
        commandAdquire(commandVector);
    else if(commandType == "modifica" && commandVector.size() == 3)
        commandModifica(commandVector);
    else if(commandType == "maisouro" && fase == F_RECOLHA)
        commandMaisOuro(commandVector);
    else if(commandType == "maisprod" && fase == F_RECOLHA)
        commandMaisProd(commandVector);
    else if(commandType == "maismilitar" && fase == F_RECOLHA)
        commandMaisMilitar(commandVector);
    else if (commandType == "toma" && commandVector.size() == 3)
        commandToma(commandVector);
    else if (commandType == "grava" && commandVector.size() == 2)
        commandGrava(commandVector);
    else if (commandType == "ativa" && commandVector.size() == 2)
        commandAtiva(commandVector);
    else if (commandType == "apaga" && commandVector.size() == 2)
        commandApaga(commandVector);
    else if (commandType == "passa" && fase == F_CONQUISTA)
        nextFase();
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

void Interface::incrementTurno() {
    if(turno < 6)
        turno++;
    else {
        // turno = 0; // TODO: Check this
        ano ++;
    }
}

void Interface::nextFase() {
    if(fase == F_EVENTOS) {
        fase = F_CONQUISTA;
        incrementTurno();
    } else fase++;

    switch (fase) {
        case F_RECOLHA:
            mundo->getImperio()->recolheMaterias();
            break;

        case F_EVENTOS:
            triggerEvent();
            break;
        
        default:
            break;
    }
        
}

string Interface::getFaseName() {
    if(fase == F_CONFIG) return "CONFIGURA";
    else if(fase == F_CONQUISTA) return "CONQUISTA/PASSA";
    else if(fase == F_COMPRA) return "COMPRA";
    else if(fase == F_RECOLHA) return "RECOLHA";
    else if(fase == F_EVENTOS) return "EVENTOS";
    else return "";
}

int Interface::getTurnos() {
    return turno;
}

void Interface::commandCria(vector<string> commandVector) {
    if(mundo->criaTerritorios(commandVector[1], stoi(commandVector[2])))
        o_stream << commandVector[1] << " criado com sucesso!" << endl;

}

void Interface::commandCarrega(vector<string> commandVector) {
    if(!readFromFile(commandVector[1]))
        o_stream << "[ERRO] Ficheiro invalido!" << endl;
    else
        o_stream << "Ficheiro lido com sucesso!" << endl;
}

void Interface::commandLista(vector<string> commandVector) {
    // lista -> Lista info do imperio
    if(commandVector.size() == 1)
        o_stream << mundo->lista() << endl;

    // lista conquistados -> Lista os territorios conquistados pelo imperio
    // lista <nome_do_territorio> -> Lista info do dado territorio
    // lista <tipo_de_territorio> -> Lista os territorios do tipo dado
    else
        o_stream << mundo->lista(commandVector[1]) << endl;

}

void Interface::commandConquista(vector<string> commandVector) {
    Imperio* imperio = mundo->getImperio();
    Territorio* territorioAConquistar = mundo->getTerritorioByName(commandVector[1]);

    if(territorioAConquistar != NULL && imperio->conquistar(territorioAConquistar))
        o_stream << "Territorio [" << territorioAConquistar->getNome() << "] conquistado!!" << endl;
    else if(territorioAConquistar == NULL)
        o_stream << "Introduza uma territorio valido!!" << endl;
    else
        o_stream << "Conquista Falhada!!" << endl;
}

void Interface::commandAdquire(vector<string> commandVector) {
    int commandResult;

    if(commandVector.size() == 2 ) {
        commandResult = mundo->imperioAdquireTecnologia(commandVector[1]);

        if(commandResult == 0)
            o_stream << "[SUCCESS] Tecnologia adquirida com sucesso!" << endl;
        else if(commandResult == -1)
            o_stream << "[ERRO] A tecnologia que pretende adquirir nao existe" << endl;
        else if(commandResult == -2)
            o_stream << "[ERRO] Nao tem dinheiro suficiente para comprar esta tecnologia" << endl;
        else if(commandResult == -3)
            o_stream << "[ERRO] Tecnologia ja foi adquirida" << endl;
    } else
        o_stream << "[ LOJA ]" << endl
            << "drone_militar: " << DroneMilitar::custo << " ouro" << endl
            << "misseis_teleguiados: " << MisseisTeleguiados::custo << " ouro" << endl
            << "defesas_territoriais: " << DefesasTerritoriais::custo << " ouro" << endl
            << "bolsa_de_valores: " << BolsaValores::custo << " ouro" << endl
            << "banco_central: " << BancoCentral::custo << " ouro" << endl;
}

void Interface::commandModifica(vector<string> commandVector) {
    Imperio* imperio = mundo->getImperio();
    int commandResult = imperio->modifica(commandVector[1], stoi(commandVector[2]));

    if(commandResult == 0)
        o_stream << "[SUCCESS] Novo valor de " << commandVector[1] << " e " << commandVector[2] << " unidades." << endl;
    else if(commandResult == -1)
        o_stream << "[ERRO] Tipo de recurso invalido. Este deve ser 'ouro' ou 'prod'." << endl;
    else if(commandResult == -2)
        o_stream << "[ERRO] A quantidade que inseriu e superior a capacidade do imperio: " << imperio->getMaxUnidades() << " unidades." << endl;

}

void Interface::commandMaisOuro(vector<string> commandVector) {
    Imperio* imperio = mundo->getImperio();
    int commandResult = imperio->maisOuro();

    if(commandResult == 0)
        o_stream << "[SUCCESS] Troca efetuada com sucesso! Total de ouro: " << imperio->getArmazemOuro() << " unidades." << endl;
    else if(commandResult == -1)
        o_stream << "[ERRO] Falha ao efetuar troca. Nao tem produtos suficientes para trocar." << endl;
    else if(commandResult == -2)
        o_stream << "[ERRO] Impossivel efetuar troca. Ainda nao adquiriu a tecnologia Bolsa de valores." << endl;
    else if(commandResult == -3)
        o_stream << "[ERRO] Falha ao efetuar troca. Nao tem mais espaco no armazem de ouro." << endl;
}

void Interface::commandMaisProd(vector<string> commandVector) {
    Imperio* imperio = mundo->getImperio();
    int commandResult = imperio->maisProd();

    if(commandResult == 0)
        o_stream << "[SUCCESS] Troca efetuada com sucesso! Total de produtos: " << imperio->getArmazemProds() << " unidades." << endl;
    else if(commandResult == -1)
        o_stream << "[ERRO] Falha ao efetuar troca. Nao tem ouro suficiente para trocar." << endl;
    else if(commandResult == -2)
        o_stream << "[ERRO] Impossivel efetuar troca. Ainda nao adquiriu a tecnologia Bolsa de valores." << endl;
    else if(commandResult == -3)
        o_stream << "[ERRO] Falha ao efetuar troca. Nao tem mais espaco no armazem de produtos." << endl;

}

void Interface::commandMaisMilitar(vector<string> commandVector) {
    Imperio* imperio = mundo->getImperio();
    int commandResult = imperio->maisMilitar();

    if(commandResult == 0)
        o_stream << "[SUCCESS] Troca efetuada com sucesso! Forca militar atual: " << imperio->getForcaMilitar() << " unidades." << endl;
    else if(commandResult == -1)
        o_stream << "[ERRO] Falha ao efetuar troca. Nao tem ouro e/ou produtos suficiente para trocar." << endl;
    else if(commandResult == -2)
        o_stream << "[ERRO] Impossivel efetuar troca. Ainda nao adquiriu a tecnologia Bolsa de valores." << endl;
    else if(commandResult == -3)
        o_stream << "[ERRO] Falha ao efetuar troca. Ja atingiu o valor de forca militar maximo." << endl;

}

void Interface::commandToma(vector<string> commandVector) {
    int commandResult = mundo->tomaCommand(commandVector[1], commandVector[2]);

    if(commandVector[1] == "terr") {
        if(commandResult == 0)
            o_stream << "[SUCCESS] Territorio tomado com sucesso!" << endl;
        else if(commandResult == -1)
            o_stream << "[ERRO] O territorio que pretende tomar ja foi conquistado" << endl;
        else if(commandResult == -2)
            o_stream << "[ERRO] O territorio que pretende tomar nao existe" << endl;

    }  else if(commandVector[1] == "tec") {
        if(commandResult == 0)
            o_stream << "[SUCCESS] Tecnologia tomada com sucesso!" << endl;
        else if(commandResult == -1)
            o_stream << "[ERRO] A tecnologia que pretende tomar nao existe" << endl;
        else if(commandResult == -2)
            o_stream << "[ERRO] Tecnologia ja foi adquirida" << endl;
    } else if(commandResult == -4) {
        o_stream << "[ERRO] Tipo a tomar invalido" << endl;
    }
}

void Interface::commandGrava(vector<string> commandVector) {
    savedSnapshots.push_back(new MundoSnapshot(commandVector[1], mundo->clone()));
    o_stream << "Nova snapshot com o nome '" << commandVector[1] << "' foi guardada com sucesso" << endl;
}

void Interface::commandAtiva(vector<string> commandVector) {
    for(auto it = savedSnapshots.begin(); it < savedSnapshots.end(); it++) {
        if((*it)->getName() == commandVector[1]) {
            delete mundo;
            mundo = (*it)->getSavedMundo()->clone();
            o_stream << "Snapshot com o nome '" << commandVector[1] << "' foi recuperada com sucesso" << endl;
            return;
        }
    }
    o_stream << "Nao existe nenhuma snapshot com o nome '" << commandVector[1] << "'." << endl;
}

void Interface::commandApaga(vector<string> commandVector) {
    for(auto it = savedSnapshots.begin(); it < savedSnapshots.end(); it++) {
        if((*it)->getName() == commandVector[1]) {
            delete (*it)->getSavedMundo();
            
            savedSnapshots.erase(it);
            o_stream << "Snapshot com o nome '" << commandVector[1] << "' foi apagada com sucesso" << endl;
            return;
        }
    }
    o_stream << "Nao existe nenhuma snapshot com o nome '" << commandVector[1] << "'." << endl;

}

void Interface::triggerEvent() {
    int eventBeingTriggered = randNum(0, 3);

    switch (eventBeingTriggered) {
        case 0:
            eventRecursoAbandonado();
            break;
        case 1:
            eventInvasao();
            break;
        case 2:
            eventAliancaDiplomatica();
            break;
        case 3: // No event triggered
            o_stream << "[ EVENTO ] Nao ocorreu nenhum evento." << endl;
        default:
            break;
    }
}

void Interface::eventRecursoAbandonado() {
    Imperio* imperio = mundo->getImperio();

    o_stream << "[ EVENTO ] Evento de recurso abandonado a comecar..." << endl;
    o_stream << "[ EVENTO ] Ganhou uma unidade de ";

    if(ano == 1) {
        imperio->incrementProd();
        o_stream << "produtos!   Produtos: " << imperio->getArmazemProds();
    } else {
        imperio->incrementOuro();
        o_stream << "ouro!   Ouro: " << imperio->getArmazemOuro();
    }

    o_stream << endl;
}

void Interface::eventInvasao() {
    o_stream << "[ EVENTO ] Evento de invasao a comecar..." << endl;

    Imperio* imperio = mundo->getImperio();
    int invasionResult = imperio->sufferInvasion(ano, o_stream);

    if(invasionResult == -1){  // Game lost
        o_stream << "[ INFO ] Ficou sem territorios conquistados. Perdeu o jogo" << endl;
        // CALL FUNCTION TO FINISH THE GAME
    }
}

void Interface::eventAliancaDiplomatica() {
    Imperio* imperio = mundo->getImperio();
    imperio->incrementForcaMilitar();

    o_stream << "[ EVENTO ] Evento de aliança diplomática a comecar..." << endl;
    o_stream << "[ EVENTO ] Ganhou uma unidade de forca militar!   Forca militar: " << imperio->getForcaMilitar() << endl;
}


