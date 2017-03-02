//
// Created by lirfu on 27.02.17..
//

#include "QIGA.h"
#include "QuantumRegister.h"

QIGA::QIGA(QuantumLookupTable *lookupTable) {
    name_ = "QIGA";
    rotationGate_ = lookupTable;
}

bool QIGA::advanceGeneration(StateP state, DemeP deme) {

    // Measure the population to generate the classical bit strings.
    for (uint i = 0; i < deme->size(); i++) {
        ((QuantumRegister *) deme->at(i)->getGenotype().get())->measure(state);
    }

    // Evaluate the population.
    for (uint i = 0; i < deme->size(); i++)
        evaluate(deme->at(i));

    // Store the best solution.
    IndividualP best = (deme->hof_->getBest().at(0)); // Guess best.

    // Find actual best.
    for (uint i = 1; i < deme->size(); i++) {
        IndividualP temp = (deme->at(i));
        if (temp->fitness->isBetterThan(best->fitness))
            best = temp;
    }

    // Update the rest of the population with rotation gates.
    for (uint i = 1; i < deme->size(); i++)
        rotationGate_->performQuantumGateRotation(deme->at(i), best);

    // For new population measure binaries.
    for (uint i = 1; i < deme->size(); i++)
        ((QuantumRegister *) deme->at(i)->getGenotype().get())->update();

    return true;
}