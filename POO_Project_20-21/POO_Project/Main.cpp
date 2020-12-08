#include <iostream>
#include "Territorio.h"
#include "Imperio.h"
#include <time.h>
#include "Interface.h"

using namespace std;

void initRandom() {
	srand(time(NULL));		//previne repeticoes entre runs
}

int main() {
	initRandom();
	
    Interface i(new Mundo(), cin, cout);
    i.run();
}