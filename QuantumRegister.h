//
// Created by lirfu on 27.02.17..
//

#ifndef QUANTUMINSPIREDGENETICALGORITHM_QUANTUMREGISTER_H
#define QUANTUMINSPIREDGENETICALGORITHM_QUANTUMREGISTER_H

#include "ecf/ECF.h"

class QuantumRegister : public Binary::Binary {

public:

    QuantumRegister();

    bool initialize(StateP);

    void registerParameters(StateP);

    QuantumRegister *copy() {
        QuantumRegister *newObject = new QuantumRegister(*this);
        return newObject;
    }

//    void write(XMLNode &xQuantumRegister);

//    void read(XMLNode &xQuantumRegister);

//    void measure(vector<bool> &);

    void measure(StateP);

private:

    vector<double> alphas_;

//    std::default_random_engine generator;
//    std::uniform_real_distribution<double> distribution(0.0, 1.0);
};

typedef boost::shared_ptr<QuantumRegister> QuantumRegisterP;

#endif //QUANTUMINSPIREDGENETICALGORITHM_QUANTUMREGISTER_H
