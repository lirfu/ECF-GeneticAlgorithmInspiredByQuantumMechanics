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
    // The bounds are set for percentages [0, 1].
//    Genotype::setParameterValue(state, std::string("lbound"), (voidP) (new double(0)));
//    Genotype::setParameterValue(state, std::string("ubound"), (voidP) (new double(1)));

    if (!isParameterDefined(state, "precision"))
        Genotype::setParameterValue(state, std::string("precision"), (voidP) (new double(3)));

    Binary::initialize(state);

    // Set all qbits into superposition.
    for (uint i = 0; i < variables.size() * nBits_; i++)
        thetas_.push_back(M_PI / 2);

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
    for (uint variable = 0; variable < nDimension_; variable++) {
        for (uint bit = 0; bit < nBits_; bit++) {
            // Measure the qbit state based on alpha squared.
            result = state->getRandomizer()->getRandomDouble() > pow(cos(thetas_[variable * bit] / 2), 2);

            variables[variable][bit] = result;
        }
    }

}