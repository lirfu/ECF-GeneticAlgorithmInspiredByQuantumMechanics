//
// Created by lirfu on 27.02.17..
//

#include "QIGA.h"

QIGA::QIGA() {
    name_ = "QIGA";
}

void QIGA::registerParameters(StateP state) {
    Algorithm::registerParameters(state);

    registerParameter(state, "qrot.ubound", (voidP) (new double(0.1)), ECF::DOUBLE,
                      "upper bound of the theta delta (gets multiplied by M_PI)(default: 0.1).");
    registerParameter(state, "qrot.lbound", (voidP) (new double(0.01)), ECF::DOUBLE,
                      "lower bound of the theta delta (gets multiplied by M_PI)(default: 0.01).");
    registerParameter(state, "disaster", (voidP) (new uint(-1)), ECF::UINT,
                      "number of repeated best individuals before triggering the disaster operator.");
}

bool QIGA::initialize(StateP state) {
    Algorithm::initialize(state);

    double ubound = *((double *) getParameterValue(state, "qrot.ubound").get());
    double lbound = *((double *) getParameterValue(state, "qrot.lbound").get());
    rotationGate_ = new QuantumRotationGate(lbound, ubound);

    disasterTrigger_ = *((uint *) getParameterValue(state, "disaster").get());
    disasterEnabled_ = disasterTrigger_ != (uint) -1;

    return true;
}

bool QIGA::advanceGeneration(StateP state, DemeP deme) {

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

    // Check if disaster operator is needed (when the algorithm is stuck in a local optimum).
    bool triggerDisaster = disasterEnabled_ && isDisasterTriggered(best->fitness->getValue());
    if (triggerDisaster)
        cout << "Performing disaster" << endl;

    // Update the rest of the population with quantum operators.
    for (uint i = 0; i < deme->size(); i++) {

        // Best individual is left intact (elitism).
        if (i != indexOfBest) {

            // Execute the disaster operator if needed.
            if (triggerDisaster) {
                ((QuantumRegister *) deme->at(i)->getGenotype().get())->initialize(state);
            }

            // Use the quantum rotation gate to converge the individual toward the best, performs local space search.
            rotationGate_->performQuantumGateRotation(state, deme->at(i), best);

            // Mutate the individual, helps with global space search.
            mutate(deme->at(i));

        }

        // Measure the new individual to generate a classical bit string, helps with global space search.
        ((QuantumRegister *) deme->at(i)->getGenotype().get())->measure(state);

        // Update the register's real values, needed for evaluation.
        ((QuantumRegister *) deme->at(i)->getGenotype().get())->update();

        // Evaluate the individual.
        evaluate(deme->at(i));
    }

    return true;
}

bool QIGA::isDisasterTriggered(double bestFitness) {

    if (bestFitness != bestFitness) { // Fitness changed, no local optimal detected.

        disasterCouter_ = 0;
        disasterBestFitness_ = bestFitness;
        return false;

    } else { // Local optima detected (same best fitness repeated).

        if (disasterCouter_ == disasterTrigger_) { // Local optima repeated too many times, disaster triggered.

            disasterCouter_ = 0;
            return true;

        } else { // Repeated fitness, one step closer to disaster.

            disasterCouter_++;
            return false;

        }
    }
}
