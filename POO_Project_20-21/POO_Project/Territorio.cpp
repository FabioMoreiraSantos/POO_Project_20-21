#include "Territorio.h"
#include "sstream"

int Territorio::nTerritorios = 1;		//inicializar a variavel static

//Construtor por omissao
// Territorio(string n)
// {
// 	nome = (string) n + to_string(nTerritorios);
// 	resistencia = 9;
// 	criacaoOuro = 1;
// 	criacaoProdutos = 1;
// 	pVitoria = 0;
// 	nTerritorios++;
// }

string Territorio::getNome() {
	return nome;
}


