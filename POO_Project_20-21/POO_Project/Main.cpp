#include <iostream>
#include "Mundo.h"

using namespace std;

int main() {
	// Territorio t1, t2, t3, t4;
    Mundo mundo;

    mundo.configurarMundo();

    cout << mundo.getAsString() << endl;
}