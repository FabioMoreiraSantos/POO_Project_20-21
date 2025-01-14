#include "Interface.h"
#include "Tecnologia.h"
#include <iostream>

using namespace std;

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

    o_stream << endl
             << "##########################  Bem vindo jogador!  ##########################" << endl
             << "    Digite o comando 'help' para ver a lista de comandos disponivels" << endl << endl << endl;

    while(true) {
        o_stream <<"\n[Ano " << getAno() << "]"
            "[Turno: " << getTurnos() << "]" << endl
            << "[" << getFaseName() << "] Commando: ";
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
    else if(commandType == "fevento")
        commandFevento(commandVector);
    else if(commandType == "help")
        commandHelp();
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
        turno = 0;
        ano ++;
    }
}

void Interface::nextFase() {
    Imperio* imperio = mundo->getImperio();
    if(turno == 12 && ano == 2)
        finishGame();
    
    if(fase == F_EVENTOS) { // Change turno
        fase = F_CONQUISTA;
        incrementTurno();
        hasUserConquered = false;
        imperio->triggerTurnBasedTerrActions();
    } else fase++;

    switch (fase) {
        case F_RECOLHA:
            imperio->recolheMaterias(o_stream);
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

int Interface::getAno() {
        return ano;
}

bool is_number(const std::string& s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

void Interface::commandCria(vector<string> commandVector) {
    if(commandVector.size() == 3) {
        if (is_number(commandVector[2])) {
            if (mundo->criaTerritorios(commandVector[1], stoi(commandVector[2])))
                o_stream << commandVector[1] << " criado com sucesso!" << endl << endl;
            else
                o_stream << "Nao existe nenhum territorio com o nome '" << commandVector[1] << "'" << endl << endl;
        }
        else {
            o_stream << "[ ERRO ] Digite um numero. Por favor use a seguinte estrutura:" << endl
                << "       cria <tipo_territorio> <n_territorios>" << endl << endl;
        }
    } else
        o_stream << "[ ERRO ] Formato do comando invalido. Por favor use a seguinte estrutura:" << endl
                 << "       cria <tipo_territorio> <n_territorios>" << endl << endl;
}



void Interface::commandCarrega(vector<string> commandVector) {
    if(commandVector.size() == 2) {
        if(!readFromFile(commandVector[1]))
            o_stream << "[ERRO] Ficheiro invalido!" << endl;
        else
            o_stream << "Ficheiro lido com sucesso!" << endl;
    } else
        o_stream << "[ ERRO ] Formato do comando invalido. Por favor use a seguinte estrutura:" << endl
                 << "       carrega <nome_ficheiro>" << endl << endl;
}

void Interface::commandLista(vector<string> commandVector) {
    // lista -> Lista info do imperio
    if(commandVector.size() == 1)
        o_stream << mundo->lista() << endl;

    // lista conquistados -> Lista os territorios conquistados pelo imperio
    // lista por_conquistar -> Lista todos os territorio que ainda nao foram conquistados
    // lista <nome_do_territorio> -> Lista info do dado territorio
    // lista <tipo_de_territorio> -> Lista os territorios do tipo dado
    // lista tecnologias -> Lista todas as tecnologias e suas informacoes
    else if(commandVector.size() == 2)
        o_stream << mundo->lista(commandVector[1]) << endl;
    else
        o_stream << "[ ERRO ] Formato do comando invalido. Por favor use a seguinte estrutura:" << endl
                 << "       lista" << endl
                 << "       lista <tipo_listagem>" << endl << endl;
}

void Interface::commandConquista(vector<string> commandVector) {
    if(commandVector.size() != 2)
        o_stream << "[ ERRO ] Formato do comando invalido. Por favor use a seguinte estrutura:" << endl
                 << "       conquista <nome_territorio>" << endl << endl;
    else
        if(!hasUserConquered) {
            Imperio* imperio = mundo->getImperio();
            Territorio* territorioAConquistar = mundo->getTerritorioByName(commandVector[1]);
            int commandResult;
            hasUserConquered = true;
            
            if(territorioAConquistar == NULL)
                o_stream << "Introduza uma territorio valido!!" << endl;
            else {
                commandResult = imperio->conquistar(territorioAConquistar, o_stream);
                switch (commandResult) {
                    case 0:
                        o_stream << "Territorio [" << territorioAConquistar->getNome() << "] conquistado!!" << endl;
                        break;
                    case -1:
                        o_stream << "Conquista Falhada!!" << endl;
                    case -2:
                        o_stream << "Nao pode conquistar este territorio. Precisa de misseis teleguiados e de pelo menos 5 territorios conquistados" << endl;
                        break;
                    default:
                        break;
                    }
                }
        } else {
            o_stream << "[ ERRO ] Ação proibida. Já tentou conquistar um territorio este turno." << endl;
        }
}

void Interface::commandAdquire(vector<string> commandVector) {
    int commandResult;

    if(commandVector.size() == 2 ) {
        Imperio* imperio = mundo->getImperio();
        commandResult = imperio->adquirirTecnologia(commandVector[1]);

        if(commandResult == 0)
            o_stream << "[SUCCESS] Tecnologia adquirida com sucesso!" << endl;
        else if(commandResult == -1)
            o_stream << "[ERRO] A tecnologia que pretende adquirir nao existe" << endl;
        else if(commandResult == -2)
            o_stream << "[ERRO] Nao tem dinheiro suficiente para comprar esta tecnologia" << endl;
        else if(commandResult == -3)
            o_stream << "[ERRO] Tecnologia ja foi adquirida" << endl;
    } else if(commandVector.size() == 1 )
        o_stream << "[ LOJA ]" << endl
            << "drone_militar: " << DroneMilitar::custo << " ouro" << endl
            << "misseis_teleguiados: " << MisseisTeleguiados::custo << " ouro" << endl
            << "defesas_territoriais: " << DefesasTerritoriais::custo << " ouro" << endl
            << "bolsa_de_valores: " << BolsaValores::custo << " ouro" << endl
            << "banco_central: " << BancoCentral::custo << " ouro" << endl;
    else
        o_stream << "[ ERRO ] Formato do comando invalido. Por favor use a seguinte estrutura:" << endl
                 << "       adquire" << endl
                 << "       adquire <nome_tecnologia>" << endl << endl;
}

void Interface::commandModifica(vector<string> commandVector) {
    Imperio* imperio;
    int commandResult;

    if(commandVector.size() == 3) {
        if (is_number(commandVector[2])) {
            imperio = mundo->getImperio();
            commandResult = imperio->modifica(commandVector[1], stoi(commandVector[2]));

            if (commandResult == 0)
                o_stream << "[SUCCESS] Novo valor de " << commandVector[1] << " e " << commandVector[2] << " unidades." << endl;
            else if (commandResult == -1)
                o_stream << "[ERRO] Tipo de recurso invalido. Este deve ser 'ouro' ou 'prod'." << endl;
            else if (commandResult == -2)
                o_stream << "[ERRO] A quantidade que inseriu e superior a capacidade do imperio: " << imperio->getMaxUnidades() << " unidades." << endl;
        }
        else {
            o_stream << "[ ERRO ] Digite um numero. Por favor use a seguinte estrutura:" << endl
                << "       modifica ouro|prod <quant>" << endl << endl;
        }

    } else
        o_stream << "[ ERRO ] Formato do comando invalido. Por favor use a seguinte estrutura:" << endl
                 << "       modifica ouro|prod <quant>" << endl << endl;
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
    int commandResult;
    
    if(commandVector.size() == 3) {
        commandResult = mundo->tomaCommand(commandVector[1], commandVector[2]);

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
    } else
        o_stream << "[ ERRO ] Formato do comando invalido. Por favor use a seguinte estrutura:" << endl
                 << "       toma terr|tec <nome_territorio|nome_tecnologia>" << endl << endl;
}

void Interface::commandGrava(vector<string> commandVector) {
    if(commandVector.size() == 2) {
        savedSnapshots.push_back(new MundoSnapshot(commandVector[1], mundo->clone()));
        o_stream << "Nova snapshot com o nome '" << commandVector[1] << "' foi guardada com sucesso" << endl;
    } else
        o_stream << "[ ERRO ] Formato do comando invalido. Por favor use a seguinte estrutura:" << endl
                 << "       grava <nome_snapshot>" << endl << endl;
}

void Interface::commandAtiva(vector<string> commandVector) {
    if(commandVector.size() == 2) {
        for(auto it = savedSnapshots.begin(); it < savedSnapshots.end(); it++) {
            if((*it)->getName() == commandVector[1]) {
                delete mundo;
                mundo = (*it)->getSavedMundo()->clone();
                o_stream << "Snapshot com o nome '" << commandVector[1] << "' foi recuperada com sucesso" << endl;
                return;
            }
        }
        o_stream << "Nao existe nenhuma snapshot com o nome '" << commandVector[1] << "'." << endl;
    } else
        o_stream << "[ ERRO ] Formato do comando invalido. Por favor use a seguinte estrutura:" << endl
                 << "       ativa <nome_snapshot>" << endl << endl;
}

void Interface::commandApaga(vector<string> commandVector) {
    if(commandVector.size() == 2) {
        for(auto it = savedSnapshots.begin(); it < savedSnapshots.end(); it++) {
            if((*it)->getName() == commandVector[1]) {
                delete (*it)->getSavedMundo();
                
                savedSnapshots.erase(it);
                o_stream << "Snapshot com o nome '" << commandVector[1] << "' foi apagada com sucesso" << endl;
                return;
            }
        }
        o_stream << "Nao existe nenhuma snapshot com o nome '" << commandVector[1] << "'." << endl;
    } else
        o_stream << "[ ERRO ] Formato do comando invalido. Por favor use a seguinte estrutura:" << endl
                 << "       apaga <nome_snapshot>" << endl << endl;

}

void Interface::commandFevento(vector<string> commandVector) {
    if(commandVector.size() == 1)
        o_stream << "[ INFO ] Eventos disponiveis: 'invasao', 'recurso_abandonado', 'alianca_diplomatica'" << endl << endl;
    else if(commandVector.size() == 2) {
        if(commandVector[1] == "invasao")
            eventInvasao();
        else if(commandVector[1] == "recurso_abandonado")
            eventRecursoAbandonado();
        else if(commandVector[1] == "alianca_diplomatica")
            eventAliancaDiplomatica();
        else
            o_stream << "[ ERRO ] Evento invalido" << endl;
    } else
        o_stream << "[ ERRO ] Formato do comando invalido. Por favor use a seguinte estrutura:" << endl
                 << "       fevento <nome_evento>" << endl << endl;
}

void Interface::commandHelp() {
    o_stream << "[ HELP ]" << endl
        << "carrega <nome_ficheiro> - Carrega um ficheiro com um conjunto de comandos e executa-os" << endl << endl
        << "cria <tipo_terr> <N> - Cria N territorios do tipo_terr e adiciona-os ao mundo." << endl
        << "      tipo_terr: planicie, montanha, fortaleza, mina, duna, castelo, refugio_de_piratas, pescaria." << endl << endl
        << "conquista <nome> - Dá ordem ao imperio para invadir e tentar conquistar um determinado territorio" << endl
        << "          nome: planicie1, montanha3, ilha2, duna10, ..." << endl << endl
        << "passa - Neste turno nao pretende conquistar mais nenhum territorio" << endl << endl
        << "maisouro - obtem 1 unidade de ouro em troca de 2 unidade de produtos" << endl << endl
        << "maisprod - obtem 1 unidade de produtos em troca de 2 unidade de ouro" << endl << endl
        << "maismilitar - obtem 1 forca militar em troca de 1 unidade de ouro e 1 unidade de produtos" << endl << endl
        << "adquire - Ver lista, custos e informacao sobre as tecnologias" << endl << endl
        << "adquire <tipo> - Adquire uma tecnologia" << endl << endl
        << "lista - Lista informacao sobre o imperio" << endl << endl
        << "lista conquistados - Lista os territorios conquistados pelo imperio" << endl << endl
        << "lista por_conquistar - Lista todos os territorios no mundo que ainda nao foram conquistados" << endl << endl
        << "lista territorios - Lista todos os territorios no mundo" << endl << endl
        << "lista <nome_territorio> - Lista todas as informacoes do territorio em questao" << endl << endl
        << "lista tecnologias - Lista todas as tecnologias existentes e seus detalhes" << endl << endl
        << "avanca - Avanca para a fase seguinte" << endl << endl
        << "grava <nomeSnapshot> - Grava em memoria uma snapshot com um determinado nome do estado atual do jogo" << endl << endl
        << "ativa <nomeSnapshot> - Restaura o estado de uma snapshot guardada em memoria" << endl << endl
        << "apaga <nomeSnapshot> - Apaga uma snapshot da memoria" << endl << endl
        << "[DEBUG] toma <terr|tec> <nome> - Toma de assalto um determinado territorio ou tecnologia, sem pagar o seu custo" << endl << endl
        << "[DEBUG] modifica <ouro|prod> <quant> - Modifica as quantidades de ouro ou produtos no imperio, sem passar do limite" << endl << endl
        << "[DEBUG] fevento <nome_evento> - Forca a ocorrencia de um evento" << endl
        << "        nome_evento: 'invasao', 'recurso_abandonado', 'alianca_diplomatica" << endl << endl
        << endl;
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
        finishGame();
    }
}

void Interface::eventAliancaDiplomatica() {
    Imperio* imperio = mundo->getImperio();
    imperio->incrementForcaMilitar();

    o_stream << "[ EVENTO ] Evento de aliança diplomatica a comecar..." << endl;
    o_stream << "[ EVENTO ] Ganhou uma unidade de forca militar!   Forca militar: " << imperio->getForcaMilitar() << endl;
}

void Interface::finishGame() {
    Imperio* imperio = mundo->getImperio();
    int score = imperio->getPontosVitoria() + imperio->getTecnologiasCount();

    if(imperio->getTecnologiasCount() == 5)
        score++;
    
    if(mundo->getTerritoriosCount() == imperio->getReinadoSize())
        score += 3;

    o_stream << "[   FIM DE JOGO   ] Terminou o jogo!!" << endl << endl
    << "SCORE FINAL: " << score << endl << endl;

    exit(0);
}
