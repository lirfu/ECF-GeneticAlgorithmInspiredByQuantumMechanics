#include <ecf/ECF.h>
#include "NNErrorEvalOp.h"
#include "NeuralNetwork.h"


void NNErrorEvalOp::registerParameters(StateP state) {
}


bool NNErrorEvalOp::initialize(StateP state) {
    return true;
}


FitnessP NNErrorEvalOp::evaluate(IndividualP individual) {
    NeuralNetwork *gen = (NeuralNetwork *) individual->getGenotype().get();

    // evaluation creates a new fitness object using a smart pointer
    // in our case, we try to minimize the function value, so we use FitnessMin fitness (for minimization problems)
    FitnessP fitness(new FitnessMin);

    double fit = gen->getTotalError();
    Errors_.push_back(fit);
    fitness->setValue(fit);
    return fitness;
}
