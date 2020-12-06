#include <iostream>
#include "Territorio.h"
#include "Imperio.h"
#include <time.h>

using namespace std;

void initRandom() {
	srand(time(NULL));		//previne repeticoes entre runs
}

int main() {

	initRandom();

	Territorio t1, t2;
	Imperio i1;

	t1.setResistencia(3);
	t2.setResistencia(3);

	cout << t1.getNome() << endl;
	cout << i1.getVectorImperio() << endl;

	i1.conquistar(&t1);
	i1.conquistar(&t2);

	cout << i1.getVectorImperio() << endl;






}