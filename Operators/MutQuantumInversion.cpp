//
// Created by lirfu on 17.03.17..
//

#include "MutQuantumInversion.h"
#include "../QuantumRegister.h"

void MutQuantumInversion::registerParameters(StateP state) {
    myGenotype_->registerParameter(state, "mut.quantum_inversion", (voidP) new double(0), ECF::DOUBLE);
}

bool MutQuantumInversion::initialize(StateP state) {
    voidP sptr = myGenotype_->getParameterValue(state, "mut.quantum_inversion");
    probability_ = *((double *) sptr.get());

    return true;
}

bool MutQuantumInversion::mutate(GenotypeP gene) {
    QuantumRegister *reg = (QuantumRegister *) (gene.get());

    // Select a qbit to invert.
    uint index = (uint) ((std::rand()) % reg->thetas_.size());

    // Invert the qbit, keeping it in the [-PI, PI] interval.
    if (reg->thetas_[index] > 0)
        reg->thetas_[index] = M_PI - reg->thetas_[index];
    else
        reg->thetas_[index] = -M_PI - reg->thetas_[index];

    return true;
}