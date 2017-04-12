#include <ecf/ECF.h>
#include <cmath>
#include "MutNeuronN.h"
#include "../NeuralNetwork.h"

// {

void MutNeuronN::registerParameters(StateP state) {
    myGenotype_->registerParameter(state, "mut.neuronN", (voidP) new double(0), ECF::DOUBLE);
}

bool MutNeuronN::initialize(StateP state) {
    voidP sptr = myGenotype_->getParameterValue(state, "mut.neuronN");
    probability_ = *((double *) sptr.get());

    return true;
}

bool MutNeuronN::mutate(GenotypeP gene) {
    NeuralNetwork *FP = (NeuralNetwork *) (gene.get());

    vector<uint> structure = FP->getLayerStructure();
    uint noLayers = FP->getNoLayers();

    uint noNeurons = 0;
    for (uint i = 1; i < structure.size(); i++) {
        noNeurons += structure[i];
    }

    uint n = state_->getRandomizer()->getRandomInteger(FP->getLBound(), FP->getUBound()) % (noNeurons) + 1;

    for (uint j = 0; j < n; j++) {
        uint chosenLayer =
                state_->getRandomizer()->getRandomInteger(FP->getLBound(), FP->getUBound()) % (noLayers - 2 + 1) + 2;
        uint chosenNeuron = state_->getRandomizer()->getRandomInteger(FP->getLBound(), FP->getUBound()) %
                            (structure[chosenLayer - 1]) + 1;

        vector<double> weights(structure[chosenLayer - 1] + 1);
        FP->getWeights(chosenLayer, chosenNeuron, weights);
        for (uint i = 0; i < weights.size(); i++) {
            weights[i] = weights[i] +
                         (state_->getRandomizer()->getRandomDouble() / (FP->getUBound() - FP->getLBound() + 1) +
                          FP->getLBound());
            if (weights[i] > FP->getUBound()) {
                weights[i] = FP->getUBound();
            }
            if (weights[i] < FP->getLBound()) {
                weights[i] = FP->getLBound();
            }
        }
        FP->setWeights(chosenLayer, chosenNeuron, weights);
    }

    return true;
}

// }
