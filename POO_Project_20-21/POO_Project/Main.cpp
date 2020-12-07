#include <iostream>
#include "Interface.h"

using namespace std;

int main() {
    Interface i(new Mundo(), cin, cout);

    i.run();
}