//
// Created by lirfu on 28.02.17..
//

#ifndef QUANTUMINSPIREDGENETICALGORITHM_QUANTUMROTATIONGATE_H
#define QUANTUMINSPIREDGENETICALGORITHM_QUANTUMROTATIONGATE_H


#include "ecf/ECF.h"
#include "../QuantumRegister.h"

class QuantumRotationGate {
public:

    QuantumRotationGate(double lbound, double ubound);

    // Performs the rotation on each register qbit.
    void performQuantumGateRotation(StateP, QuantumRegisterP, double, QuantumRegisterP, double);

public:
    double rotationH_, rotationL_;

    int getDirection(StateP, bool qi, bool bi, double a, double b);


    double getRotation(double fitX, double fitB);
};

typedef boost::shared_ptr<QuantumRotationGate> QuantumLookupTableP;

#endif //QUANTUMINSPIREDGENETICALGORITHM_QUANTUMROTATIONGATE_H
