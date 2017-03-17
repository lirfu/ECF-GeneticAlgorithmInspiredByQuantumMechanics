//
// Created by lirfu on 17.03.17..
//

#include "MutQuantumSwap.h"
#include "../QuantumRegister.h"

void MutQuantumSwap::registerParameters(StateP state) {
    myGenotype_->registerParameter(state, "mut.quantum_swap", (voidP) new double(0), ECF::DOUBLE);
}

bool MutQuantumSwap::initialize(StateP state) {
    voidP sptr = myGenotype_->getParameterValue(state, "mut.quantum_swap");
    probability_ = *((double *) sptr.get());

    return true;
}

bool MutQuantumSwap::mutate(GenotypeP gene) {
    QuantumRegister *reg = (QuantumRegister *) (gene.get());

    std::default_random_engine generator(std::random_device{}());

    // If a mutation occurs.
    if (std::rand() % (int) (100 + 100 * probability_) > 100) { // TODO Doesn't work for probabilities smaller than 0.01
        // Select the 1st qbit to swap.
        uint index1 = (uint) ((std::rand()) % reg->thetas_.size());
        // Select the 2nd qbit to swap, different from the first one.
        uint index2;
        do {
            index2 = (uint) ((std::rand()) % reg->thetas_.size());
        } while (index2 == index1);

        // swap the two qbits.
        double tmp = reg->thetas_[index1];
        reg->thetas_[index1] = reg->thetas_[index2];
        reg->thetas_[index2] = tmp;
    }


    return true;
}