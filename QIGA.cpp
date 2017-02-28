//
// Created by lirfu on 27.02.17..
//

#include "QIGA.h"
#include "QuantumRegister.h"

bool QIGA::advanceGeneration(StateP state, DemeP deme) {
    vector<BinaryP> bitStrings;

    // Measure the population to get classical bit strings.
    for (uint i = 0; i < deme->size(); i++) {
        BinaryP reg;

        ((QuantumRegister *) deme->at(i)->getGenotype().get())->measure(reg);

        bitStrings.push_back(reg);
    }

    // Evaluate the population.

    // Store the best solution and temporarily exclude from population.

    // Update the rest of the population with rotation gates.

    // Return the best to the population.

    return true;
}