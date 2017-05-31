//
// Created by lirfu on 27.02.17..
//

#include "math.h"
#include "QuantumRegister.h"
#include "Operators/MutQuantumInversion.h"
#include "Operators/MutQuantumSwap.h"

QuantumRegister::QuantumRegister() {
    name_ = "QuantumRegister";
}

std::vector<MutationOpP> QuantumRegister::getMutationOp() {
    std::vector<MutationOpP> mut;

    mut.push_back(static_cast<MutationOpP> (new MutQuantumInversion));
    mut.push_back(static_cast<MutationOpP> (new MutQuantumSwap));

    return mut;
}

std::vector<CrossoverOpP> QuantumRegister::getCrossoverOp() {
    std::vector<CrossoverOpP> crx;
// No crossover needed.
    return crx;
}

void QuantumRegister::registerParameters(StateP state) {
    Binary::Binary::registerParameters(state);

    registerParameter(state, "initAngle", (voidP) (new double(0.5)), ECF::DOUBLE,
                      "the initial angle of every qbit (must be from [0, 1])(gets multiplied with M_PI)(default: 0.5).");
}

bool QuantumRegister::initialize(StateP state) {
    if (!isParameterDefined(state, "precision"))
        Genotype::setParameterValue(state, std::string("precision"), (voidP) (new double(3)));

    Binary::Binary::initialize(state);

    resetQbits(state);

    return true;
}

void QuantumRegister::write(XMLNode &xQuantumRegister) {
    Binary::write(xQuantumRegister);
//    xQuantumRegister = XMLNode::createXMLTopNode("QuantumRegister");
//    std::stringstream sValue;
//    sValue << nDimension_;
//    xFloatingPoint.addAttribute("size", sValue.str().c_str());
//
//    sValue.str("");
//    for(uint iVar = 0; iVar < nDimension_; iVar++)
//        sValue << "\t" << realValue[iVar];
//    xFloatingPoint.addText(sValue.str().c_str());
}

void QuantumRegister::read(XMLNode &xQuantumRegister) {
    Binary::read(xQuantumRegister);
//    XMLCSTR values = xQuantumRegister.getText();
//    std::stringstream sValues;
//    sValues << values;
//
//    for(uint iVar = 0; iVar < nDimension_; iVar++) {
//        sValues >> realValue[iVar];
//    }
}

void QuantumRegister::measure(StateP state) {
    // Collapse the superpositions of qbits to a classical binary string.
    uint index = 0;
    for (uint variable = 0; variable < nDimension_; variable++) {
        for (uint bit = 0; bit < nBits_; bit++) {
            // Measure the qbit state based on alpha squared.
            variables[variable][bit] = state->getRandomizer()->getRandomDouble() > pow(cos(thetas_[index] / 2), 2);

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

void QuantumRegister::resetQbits(StateP state) {
    double superpositionThetaValue = *(double *) getParameterValue(state, "initAngle").get() * M_PI;

    ulong qbitsRequired = variables.size() * nBits_;
    thetas_.clear();

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
}
