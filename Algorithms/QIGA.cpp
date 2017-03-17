//
// Created by lirfu on 27.02.17..
//

#include "QIGA.h"
#include "../QuantumRegister.h"

QIGA::QIGA(QuantumRotationGate *lookupTable) {
    name_ = "QIGA";
    rotationGate_ = lookupTable;
}

bool QIGA::advanceGeneration(StateP state, DemeP deme) {

//    for (uint i = 0; i < deme->size(); i++)
//    {
//        ((QuantumRegister *) deme->at(i)->getGenotype().get())->printOut();
//    }

    // Store the best solution.
    IndividualP best = (deme->hof_->getBest().at(0)); // Guess the best.
    uint indexOfBest = 0;

    for (uint i = 1; i < deme->size(); i++) // Find the actual best.
    {
        IndividualP temp = (deme->at(i));
        if (temp->fitness->isBetterThan(best->fitness)) {
            best = temp;
            indexOfBest = i;
        }
    }

//    cout << "###BEST:";
//    ((QuantumRegister *) best->getGenotype().get())->printOut();

    // Update the rest of the population with quantum operators.
    for (uint i = 0; i < deme->size(); i++) {
        // Skip the best (elitism).
        if (i == indexOfBest)
            continue;

        // Use the quantum rotation gate.
        rotationGate_->performQuantumGateRotation(state, deme->at(i), best);

        // Mutate the individual.
        mutate(deme->at(i));
    }

    // Prepare and evaluate the population.
    for (uint i = 0; i < deme->size(); i++) {
        // Measure the population to generate the classical bit strings.
        ((QuantumRegister *) deme->at(i)->getGenotype().get())->measure(state);

        // Update the register's real values for evaluation.
        ((QuantumRegister *) deme->at(i)->getGenotype().get())->update();

        // Evaluate the population.
        evaluate(deme->at(i));
    }

    return true;
}