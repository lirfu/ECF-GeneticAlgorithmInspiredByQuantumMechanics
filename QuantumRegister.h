//
// Created by lirfu on 27.02.17..
//

#ifndef QUANTUMINSPIREDGENETICALGORITHM_QUANTUMREGISTER_H
#define QUANTUMINSPIREDGENETICALGORITHM_QUANTUMREGISTER_H

#include "ecf/ECF.h"

class QuantumRegister : public FloatingPoint::FloatingPoint {

public:

    QuantumRegister();

    bool initialize(StateP state);

    void registerParameters(StateP state);

    QuantumRegister *copy() {
        QuantumRegister *newObject = new QuantumRegister(*this);
        return newObject;
    }

    void write(XMLNode &xQuantumRegister);

    void read(XMLNode &xQuantumRegister);

    void measure(vector<bool> &classicalBits);

    void measure(BinaryP &classicalBits);
};

typedef boost::shared_ptr<QuantumRegister> QuantumRegisterP;

#endif //QUANTUMINSPIREDGENETICALGORITHM_QUANTUMREGISTER_H
