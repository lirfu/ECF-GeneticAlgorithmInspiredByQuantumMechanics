//
// Created by lirfu on 27.02.17..
//

#ifndef QUANTUMINSPIREDGENETICALGORITHM_QUANTUMREGISTER_H
#define QUANTUMINSPIREDGENETICALGORITHM_QUANTUMREGISTER_H

#include "ecf/ECF.h"

class QuantumRegister : public RealValueGenotype {

public:

    QuantumRegister() { name_ = "QuantumRegister"; }

    bool initialize(StateP state) { return true; }

    QuantumRegister *copy() {
        QuantumRegister *newObject = new QuantumRegister(*this);
        return newObject;
    }

    void write(XMLNode& xQuantumRegister);
    void read(XMLNode& xQuantumRegister);
};

typedef boost::shared_ptr<QuantumRegister> QuantumRegisterP;

#endif //QUANTUMINSPIREDGENETICALGORITHM_QUANTUMREGISTER_H
