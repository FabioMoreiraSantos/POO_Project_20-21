#include <iostream>
#include <time.h>
#include "Interface.h"
#include <random>

using namespace std;

int main() {
    Interface i(new Mundo(), cin, cout);
    i.run();

    // Imperio i1(new Territorio);

    // // Imperio i2(i1);
    // // Imperio i3 = i2;
}
