//
// Created by lirfu on 27.02.17..
//

#ifndef QUANTUMINSPIREDGENETICALGORITHM_QIGA_H
#define QUANTUMINSPIREDGENETICALGORITHM_QIGA_H

#include "ecf/ECF.h"
#include "../Operators/QuantumRotationGate.h"

class QIGA : public Algorithm {
public:
    QIGA(QuantumRotationGate *);

    bool advanceGeneration(StateP, DemeP);

private:
    QuantumRotationGate *rotationGate_;

};

typedef boost::shared_ptr<QIGA> QIGAP;


#endif //QUANTUMINSPIREDGENETICALGORITHM_QIGA_H
