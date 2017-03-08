//
// Created by lirfu on 28.02.17..
//

#include "QuantumLookupTable.h"


void QuantumLookupTable::performQuantumGateRotation(IndividualP reg, IndividualP best) {
    double fitnessX = reg->fitness->getValue();
    double fitnessB = best->fitness->getValue();
    QuantumRegister registerX = *(QuantumRegister *) reg->getGenotype().get();
    QuantumRegister registerB = *(QuantumRegister *) best->getGenotype().get();

    //TODO Implement the quantum rotation gate
    //Hint: calculate the math to understand how to implement it on thetas.

    uint index = 0;
    for (uint var = 0; var < registerX.variables.size(); var++)
        for (uint bit = 0; bit < registerX.variables[var].size(); bit++) {
            registerX.thetas_[index] =
                    getDirection(
                            registerX.variables[var][bit],
                            registerB.variables[var][bit],
                            cos(registerX.thetas_[index] / 2),
                            sin(registerX.thetas_[index] / 2)
                    )
                    * getRotation(fitnessX, fitnessB);


            index++;
        }
}

int QuantumLookupTable::getDirection(bool xi, bool bi, double a, double b) {
    uint column;

    if (a * b > 0)
        column = 0;
    else if (a * b < 0)
        column = 1;
    else if (a == 0)
        column = 2;
    else if (b == 0)
        column = 3;
    else
        return 0; //TODO Nothing found, throw an exception about an invalid table.

    int value = standardDirectionTable_[4 * xi + 2 * bi + column];

    if (value > 1) {
        return 1; //TODO Return a random, not 0, direction (+-1).
    } else {
        return value;
    }
}

double QuantumLookupTable::getRotation(double fitX, double fitB) {
    //TODO What if rotation must be 0?
    return rotationL_ + (rotationH_ - rotationL_) *
                        abs(fitX - fitB) / max(fitX, fitB);
}
