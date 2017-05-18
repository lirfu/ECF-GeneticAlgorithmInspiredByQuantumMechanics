//
// Created by lirfu on 27.02.17..
//

#ifndef QUANTUMINSPIREDGENETICALGORITHM_QIGA_H
#define QUANTUMINSPIREDGENETICALGORITHM_QIGA_H

#include "ecf/ECF.h"
#include "../Operators/QuantumRotationGate.h"

class GAIQM : public Algorithm {
public:
    GAIQM();

    void registerParameters(StateP state);

    bool initialize(StateP state);

    bool initializePopulation(StateP);

    bool advanceGeneration(StateP, DemeP);

private:
    bool disasterEnabled_ = false;
    uint disasterTrigger_ = 0;
    uint disasterCouter_ = 0;
    double disasterBestFitness_ = 0;

    bool isDisasterTriggered(double bestFitness);

    QuantumRotationGate *rotationGate_ = NULL;

    void adapter(IndividualP, uint);
};

typedef boost::shared_ptr<GAIQM> GAIQMP;


#endif //QUANTUMINSPIREDGENETICALGORITHM_QIGA_H
