#include <ecf/ECF.h>
#include "QIGA.h"
#include "QuantumRegister.h"
#include "FunctionMinEvalOp.h"

int main(int argc, char **argv) {
    StateP state(new State);

    FunctionMinEvalOpP eval(new FunctionMinEvalOp);
    QuantumRegisterP reg(new QuantumRegister);

    QuantumLookupTable *lookup = new QuantumLookupTable;
    QIGAP qga(new QIGA(lookup));

    state->setEvalOp(eval);
    state->addGenotype(reg);
    state->addAlgorithm(qga);

    state->initialize(argc, argv);
    state->run();
}
