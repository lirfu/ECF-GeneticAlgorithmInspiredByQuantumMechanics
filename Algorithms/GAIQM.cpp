//
// Created by lirfu on 27.02.17..
//

#include "GAIQM.h"

GAIQM::GAIQM() {
    name_ = "GAIQM";
}

void GAIQM::registerParameters(StateP state) {
    Algorithm::registerParameters(state);

    registerParameter(state, "qrot.ubound", (voidP) (new double(0.1)), ECF::DOUBLE,
                      "upper bound of the theta delta (gets multiplied by M_PI)(default: 0.1).");
    registerParameter(state, "qrot.lbound", (voidP) (new double(0.01)), ECF::DOUBLE,
                      "lower bound of the theta delta (gets multiplied by M_PI)(default: 0.01).");
    registerParameter(state, "disaster", (voidP) (new uint(-1)), ECF::UINT,
                      "number of repeated best individuals before triggering the disaster operator.");
}

bool GAIQM::initialize(StateP state) {
    Algorithm::initialize(state);

    double ubound = *((double *) getParameterValue(state, "qrot.ubound").get());
    double lbound = *((double *) getParameterValue(state, "qrot.lbound").get());
    rotationGate_ = new QuantumRotationGate(lbound, ubound);

    disasterTrigger_ = *((uint *) getParameterValue(state, "disaster").get());
    disasterEnabled_ = disasterTrigger_ != (uint) -1;

    return true;
}

bool GAIQM::initializePopulation(StateP state) {
    Algorithm::initializePopulation(state);

    DemeP deme = state->getPopulation()->getLocalDeme();

    uint indexOfQReg;
    QuantumRegister *quantumRegister;
    for (uint i = 0; i < deme->size(); i++) {
        indexOfQReg = (uint) deme->at(i)->size() - 1;
        quantumRegister = (QuantumRegister *) deme->at(i)->getGenotype(indexOfQReg).get();

        quantumRegister->measure(state);
        quantumRegister->update();

        if (indexOfQReg > 0)
            adapter(deme->at(i), indexOfQReg);

        evaluate(deme->at(i));
    }

    return true;
}

bool GAIQM::advanceGeneration(StateP state, DemeP deme) {

    // Store the best solution.
    IndividualP best = (deme->hof_->getBest().at(0)); // Guess the best.
    uint indexOfBest = 0;

    // Find the actual best.
    for (uint i = 1; i < deme->size(); i++) {
        IndividualP temp = (deme->at(i));
        if (temp->fitness->isBetterThan(best->fitness)) {
            best = temp;
            indexOfBest = i;
        }
    }

    // Check if disaster operator is needed (when the algorithm is stuck in a local optimum).
    bool triggerDisaster = disasterEnabled_ && isDisasterTriggered(best->fitness->getValue());
    if (triggerDisaster) {
        cout << "Performing population disaster!" << endl;
        ECF_LOG(state, 3, "Performing population disaster!"); // FIXME Doesn't work??
    }

    uint indexOfQReg; // The index of the QuantumRegister genotype in the Individual is always the last one.
    QuantumRegister *quantumRegister;

    // Update the rest of the population with quantum operators.
    for (uint i = 0; i < deme->size(); i++) {
        indexOfQReg = (uint) deme->at(i)->size() - 1; // Find the index of the last genotype.
        quantumRegister = (QuantumRegister *) deme->at(i)->getGenotype(indexOfQReg).get();

        // Best individual is left intact (elitism).
        if (i != indexOfBest) {

            // Execute the disaster operator if needed.
            if (triggerDisaster)
                quantumRegister->resetQbits(state);

            // Use the quantum rotation gate to converge the individual toward the best, performs local space search.
            rotationGate_->performQuantumGateRotation(
                    state,
                    boost::dynamic_pointer_cast<QuantumRegister>(deme->at(i)->getGenotype(indexOfQReg)),
                    deme->at(i)->fitness->getValue(),
                    boost::dynamic_pointer_cast<QuantumRegister>(best->getGenotype(indexOfQReg)),
                    best->fitness->getValue()
            );

            // Mutate the individual, helps with global space search.
            mutate(deme->at(i));
        }

        // Measure the new individual to generate a classical bit string, helps with local optima problem and global space search.
        quantumRegister->measure(state);

        // Update the register's real values, needed for evaluation.
        quantumRegister->update();

        // If QuantumRegister is not the only genotype.
        if (indexOfQReg > 0)

            // Update the other genotype to inherit the results.
            adapter(deme->at(i), indexOfQReg);

        // Evaluate the individual.
        evaluate(deme->at(i));
    }

    return true;
}

bool GAIQM::isDisasterTriggered(double bestFitness) {

    if (disasterCouter_ == disasterTrigger_) {
        disasterCouter_ = 0;
        return true;

    } else if (bestFitness == disasterBestFitness_) {
        disasterCouter_++;
        return false;

    } else {
        disasterCouter_ = 0;
        disasterBestFitness_ = bestFitness;
        return false;
    }

}

void GAIQM::adapter(IndividualP gen, uint indexOfQReg) {
    QuantumRegister *reg = (QuantumRegister *) gen->getGenotype(indexOfQReg).get();

    if (boost::dynamic_pointer_cast<BitString::BitString>(gen->getGenotype(0)) != nullptr) {
//        cout << "BITSTRING" << endl;

        BitString::BitString *bitstring = (BitString::BitString *) gen->getGenotype(0).get();

        uint index = 0;
        for (uint v = 0; v < reg->variables.size(); v++)
            for (uint b = 0; b < reg->variables[v].size(); b++)
                bitstring->bits[index++] = reg->variables[v][b];

    } else if (boost::dynamic_pointer_cast<FloatingPoint::FloatingPoint>(gen->getGenotype(0)) != nullptr) {
//        cout << "FLOATINGPOINT" << endl;

        FloatingPoint::FloatingPoint *realstring = (FloatingPoint::FloatingPoint *) gen->getGenotype(0).get();

        for (uint i = 0; i < realstring->realValue.size(); i++)
            realstring->realValue[i] = reg->realValue[i];

    } else if (boost::dynamic_pointer_cast<Binary::Binary>(gen->getGenotype(0)) != nullptr) {
//        cout << "BINARY" << endl;

        Binary::Binary *binarystring = (Binary::Binary *) gen->getGenotype(0).get();

        for (uint v = 0; v < reg->variables.size(); v++)
            for (uint b = 0; b < reg->variables[v].size(); b++)
                binarystring->variables[v][b] = reg->variables[v][b];

        binarystring->update();
    }
}

