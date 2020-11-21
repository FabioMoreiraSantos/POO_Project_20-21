#include <iostream>
#include "Territorio.h"
#include "Imperio.h"

using namespace std;

int main() {
	Territorio t1, t2;
	Imperio i1;

	cout << t1.getNome() << endl;
	cout << i1.getVectorImperio() << endl;

	i1.adicionaTerritorio(t1);
	i1.adicionaTerritorio(t2);

	cout << i1.getVectorImperio() << endl;


	i1.removeTerritorio(t1);

	cout << i1.getVectorImperio() << endl;


}