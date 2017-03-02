//
// Created by lirfu on 28.02.17..
//

#ifndef QUANTUMINSPIREDGENETICALGORITHM_QUANTUMLOOKUPTABLE_H
#define QUANTUMINSPIREDGENETICALGORITHM_QUANTUMLOOKUPTABLE_H


#include "ecf/ECF.h"

class QuantumLookupTable {
public:

    QuantumLookupTable() {};

    // Performs the rotation on each register qbit.
    void performQuantumGateRotation(IndividualP, IndividualP);

private:
    double rotationValues[];


};

typedef boost::shared_ptr<QuantumLookupTable> QuantumLookupTableP;

#endif //QUANTUMINSPIREDGENETICALGORITHM_QUANTUMLOOKUPTABLE_H
