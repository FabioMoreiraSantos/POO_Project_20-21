#include <iostream>
#include <time.h>
#include "Interface.h"
#include <random>

using namespace std;

int main() {
    Interface i(new Mundo(), cin, cout);
    i.run();
}
