#include <iostream>
#include "Interface.h"

using namespace std;

int main() {
    Interface i(new Mundo());
	// Territorio t1, t2, t3, t4;
	// cout << t1.getNome() << endl;

    i.criarMundo(cin, cout);
}