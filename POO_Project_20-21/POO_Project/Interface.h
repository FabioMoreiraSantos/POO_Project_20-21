#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include "Mundo.h"

using namespace std;

class Interface {
    Mundo* mundo;
    istream& i_stream;
    ostream& o_stream;

public:
    Interface(Mundo* m, istream& _cin, ostream& _cout)
    : mundo(m), i_stream(_cin), o_stream(_cout) {};

    void criarMundo();

    bool readFromFile(string filename);
    bool parseCommand(string command);
    vector<string> splitString(string str) const;

    istream& getIstream() const { return i_stream; }

};