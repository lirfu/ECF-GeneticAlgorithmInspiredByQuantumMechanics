//
// Created by lirfu on 27.02.17..
//

#include <math.h>
#include "QuantumRegister.h"

QuantumRegister::QuantumRegister() {
    name_ = "QuantumRegister";
}

void QuantumRegister::registerParameters(StateP state) {
    FloatingPoint::registerParameters(state);

    registerParameter(state, "dimension", (voidP) new uint(1), ECF::UINT, "number of qbits in register (mandatory).");
}

bool QuantumRegister::initialize(StateP state) {
    // The bounds are set for percentages [0, 1].
    Genotype::setParameterValue(state, std::string("lbound"), (voidP) (new double(0)));
    Genotype::setParameterValue(state, std::string("ubound"), (voidP) (new double(1)));

    FloatingPoint::initialize(state);

    // Set all qbits into superposition.
    for (uint i = 0; i < nDimension_; i++) {
        realValue.push_back(1. / sqrt(2));
    }

    return true;
}

// NOT NEEDED IF EXTENDING FLOATING POINT AND NOT STORING ANY PERSONAL PARAMS.
//void QuantumRegister::write(XMLNode &xQuantumRegister) {
//    xQuantumRegister = XMLNode::createXMLTopNode("QuantumRegister");
//    std::stringstream sValue;
//    sValue << nDimension_;
//    xFloatingPoint.addAttribute("size", sValue.str().c_str());
//
//    sValue.str("");
//    for(uint iVar = 0; iVar < nDimension_; iVar++)
//        sValue << "\t" << realValue[iVar];
//    xFloatingPoint.addText(sValue.str().c_str());
//}
//void QuantumRegister::read(XMLNode &xQuantumRegister) {
//    XMLCSTR values = xQuantumRegister.getText();
//    std::stringstream sValues;
//    sValues << values;
//
//    for(uint iVar = 0; iVar < nDimension_; iVar++) {
//        sValues >> realValue[iVar];
//    }
//}

void QuantumRegister::measure(vector<bool> &classicalBits) {
    // Initialize the distribution.
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    // Collapse the qbit superpositions to classical binary string.
    bool result;
    for (int i = 0; i < nDimension_; i++) {
        // Measure the qbit state based on alpha squared.
        result = distribution(generator) > pow(realValue[i], 2);

        classicalBits.push_back(result);
    }
}

void QuantumRegister::measure(BinaryP &classicalBits) {
    // Initialize the distribution.
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    // Collapse the qbit superpositions to classical binary string.
    int result;
    for (int i = 0; i < nDimension_; i++) {
        // Measure the qbit state based on alpha squared.
        result = distribution(generator) > pow(realValue[i], 2) ? 1 : 0;

        classicalBits->realValue.push_back(result);
    }
}