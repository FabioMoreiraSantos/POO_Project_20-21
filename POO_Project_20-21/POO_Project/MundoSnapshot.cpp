#include "MundoSnapshot.h"
#include "Mundo.h"

MundoSnapshot::MundoSnapshot(const MundoSnapshot& ref) {
    name = ref.getName();
    savedMundo = new Mundo(*ref.getSavedMundo());
}

MundoSnapshot::~MundoSnapshot() {
    delete savedMundo;
}

MundoSnapshot& MundoSnapshot::operator=(const MundoSnapshot& c) {
    if(this == &c) { return *this; }

    delete savedMundo;

    name = c.getName();
    savedMundo = new Mundo(*savedMundo);

    return *this;
}

string MundoSnapshot::getName() const { return name; };
Mundo* MundoSnapshot::getSavedMundo() const { return savedMundo; };
