#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Mundo.h"

using namespace std;

class Interface {
    Mundo* mundo;

public:
    Interface(Mundo* m): mundo(m) {};

    bool parseCommand(string command, ostream& o_stream) const;
    vector<string> splitString(string str) const;
    void criarMundo(istream& stream, ostream& o_stream);

};