#ifndef MundoSnapshot_HEADER
#define MundoSnapshot_HEADER

#include <iostream>
#include <vector>
#include <sstream>
#include "Mundo.h"

class Tecnologia;

using namespace std;

class MundoSnapshot {
    string name;
    Mundo* savedMundo;

public:
    MundoSnapshot();
    MundoSnapshot(string _name, Mundo* _savedMundo)
    : name(_name), savedMundo(_savedMundo) {};
    MundoSnapshot(const MundoSnapshot& ref);
    MundoSnapshot& operator=(const MundoSnapshot& c);
    ~MundoSnapshot();

    string getName() const;
    Mundo* getSavedMundo() const;
};

#endif
