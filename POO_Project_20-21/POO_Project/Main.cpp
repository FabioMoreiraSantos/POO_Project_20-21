#include <iostream>
#include "Territorio.h"
#include "Imperio.h"
#include "Continente.h"
#include <time.h>
#include "Interface.h"
#include "Tecnologia.h"
#include <random>

// template<typename Base, typename T>
// inline bool instanceof(const T*) {
//    return is_base_of<Base, T>::value;
// }

using namespace std;

// void initRandom() {
// 	srand(time(NULL));		//previne repeticoes entre runs
// }

int main() {
	// initRandom();
	
    Interface i(new Mundo(), cin, cout);
    i.run();

    // Imperio i1(new Territorio);

    // // Imperio i2(i1);
    // // Imperio i3 = i2;
}
