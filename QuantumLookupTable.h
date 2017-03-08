//
// Created by lirfu on 28.02.17..
//

#ifndef QUANTUMINSPIREDGENETICALGORITHM_QUANTUMLOOKUPTABLE_H
#define QUANTUMINSPIREDGENETICALGORITHM_QUANTUMLOOKUPTABLE_H


#include "ecf/ECF.h"
#include "QuantumRegister.h"

class QuantumLookupTable {
public:

    QuantumLookupTable() {};

    // Performs the rotation on each register qbit.
    void performQuantumGateRotation(IndividualP, IndividualP best);

private:
    double rotationH_, rotationL_;

    int getDirection(bool xi, bool bi, double a, double b);

    double getRotation(double fitX, double fitB);

    // Value 10 means +-1 (random direction).
    int standardDirectionTable_[32] = {
            0, 0, 0, 0,
            0, 0, 0, 0,
            1, -1, 0, 10,
            -1, 1, 10, 0,
            -1, 1, 10, 0,
            1, -1, 0, 10,
            0, 0, 0, 0,
            0, 0, 0, 0
    };
};

typedef boost::shared_ptr<QuantumLookupTable> QuantumLookupTableP;

#endif //QUANTUMINSPIREDGENETICALGORITHM_QUANTUMLOOKUPTABLE_H
