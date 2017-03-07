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

    // Store the best solution.
    IndividualP best = (deme->hof_->getBest().at(0)); // Guess the best.

    // Find the actual best.
    for (uint i = 1; i < deme->size(); i++) {
        IndividualP temp = (deme->at(i));
        if (temp->fitness->isBetterThan(best->fitness))
            best = temp;
    }


    // Update the rest of the population with rotation gates.
    for (uint i = 1; i < deme->size(); i++)
        rotationGate_->performQuantumGateRotation(deme->at(i), best);


    // Measure the population to generate the classical bit strings.
    for (uint i = 0; i < deme->size(); i++) {
        ((QuantumRegister *) deme->at(i)->getGenotype().get())->measure(state);
    }

    // For new population update real values.
    for (uint i = 1; i < deme->size(); i++)
        ((QuantumRegister *) deme->at(i)->getGenotype().get())->update();

//    // Evaluate the population.
//    for (uint i = 0; i < deme->size(); i++)
//        evaluate(deme->at(i));

    return true;
}