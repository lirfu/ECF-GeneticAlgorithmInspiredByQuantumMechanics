//
// Created by lirfu on 27.02.17..
//

#include <math.h>
#include "QuantumRegister.h"

QuantumRegister::QuantumRegister() {
    name_ = "QuantumRegister";
}

void QuantumRegister::registerParameters(StateP state) {
    Binary::registerParameters(state);
}

bool QuantumRegister::initialize(StateP state) {
    if (!isParameterDefined(state, "precision"))
        Genotype::setParameterValue(state, std::string("precision"), (voidP) (new double(3)));

    Binary::initialize(state);

    double superpositionThetaValue = M_PI / 2;
    ulong qbitsRequired = variables.size() * nBits_;

    // Set all qbits into superposition.
    for (uint i = 0; i < qbitsRequired; i++) {

        // Choose a positive or negative superposition state.
        if (state->getRandomizer()->getRandomInteger(2) == 0)
            thetas_.push_back(superpositionThetaValue);
        else
            thetas_.push_back(-1 * superpositionThetaValue);
    }

    // Turn into a bit string.
    measure(state);

    // Calculate the real values from the bit string.
    update();

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

void QuantumRegister::measure(StateP state) {
    // Collapse the qbit superpositions to classical binary string.
    bool result;
    uint index = 0;
    for (uint variable = 0; variable < nDimension_; variable++) {
        for (uint bit = 0; bit < nBits_; bit++) {
            // Measure the qbit state based on alpha squared.
            result = state->getRandomizer()->getRandomDouble() > pow(cos(thetas_[index] / 2), 2);

            variables[variable][bit] = result;

            index++;
        }
    }
}

void QuantumRegister::printOut() {
    cout << "[";

    for (uint i = 0; i < thetas_.size(); i++) {
        if (i > 0)
            cout << ", ";

        cout << thetas_[i];
    }

    cout << "]" << endl;
}