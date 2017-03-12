//
// Created by lirfu on 28.02.17..
//

#ifndef QUANTUMINSPIREDGENETICALGORITHM_QUANTUMROTATIONGATE_H
#define QUANTUMINSPIREDGENETICALGORITHM_QUANTUMROTATIONGATE_H


#include "ecf/ECF.h"
#include "QuantumRegister.h"

class QuantumRotationGate {
public:

    QuantumRotationGate() {};

    // Performs the rotation on each register qbit.
    void performQuantumGateRotation(StateP, IndividualP, IndividualP best);

private:
    double rotationH_ = 0.05 * M_PI, rotationL_ = 0.005 * M_PI;

    int getDirection(StateP, bool xi, bool bi, double a, double b, double fitnessX, double fitnessB);


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

typedef boost::shared_ptr<QuantumRotationGate> QuantumLookupTableP;

#endif //QUANTUMINSPIREDGENETICALGORITHM_QUANTUMROTATIONGATE_H
