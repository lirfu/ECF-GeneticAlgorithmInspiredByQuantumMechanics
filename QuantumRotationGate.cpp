//
// Created by lirfu on 28.02.17..
//

#include "QuantumRotationGate.h"


void QuantumRotationGate::performQuantumGateRotation(StateP state, IndividualP reg, IndividualP best) {
    double fitnessX = reg->fitness->getValue();
    double fitnessB = best->fitness->getValue();
    QuantumRegister *registerX = (QuantumRegister *) reg->getGenotype().get();
    QuantumRegister *registerB = (QuantumRegister *) best->getGenotype().get();

    uint index = 0; // Thetas array iterator.

    for (uint var = 0; var < registerX->variables.size(); var++)
        for (uint bit = 0; bit < registerX->variables[var].size(); bit++) {

            // Update the thetas with the new recalculated values.
            double rotValue = getRotation(fitnessX, fitnessB);
            double dir = getDirection(
                    state,
                    registerX->variables[var][bit],
                    registerB->variables[var][bit],
                    cos(registerX->thetas_[index] / 2),
                    sin(registerX->thetas_[index] / 2),
                    fitnessX,
                    fitnessB
            );

            double val =

                    2 * getRotation(fitnessX, fitnessB) *

                    getDirection(
                            state,
                            registerX->variables[var][bit],
                            registerB->variables[var][bit],
                            cos(registerX->thetas_[index] / 2),
                            sin(registerX->thetas_[index] / 2),
                            fitnessX,
                            fitnessB
                    );

//            cout << "Value: " << val << endl;

            registerX->thetas_[index] = registerX->thetas_[index] + val;

            index++;
        }
}

int QuantumRotationGate::getDirection(StateP state, bool xi, bool bi, double a, double b, double fitnessX,
                                      double fitnessB) {
    uint column;

    if (a * b > 0)
        column = 0;
    else if (a * b < 0)
        column = 1;
    else if (a == 0)
        column = 2;
    else if (b == 0)
        column = 3;
    else {
        throw ("QuantumRotationGate: invalid direction!");
    }

    uint fitnessCmp = fitnessX > fitnessB ? 1 : 0;

    uint index = 8 * xi + 4 * bi + 2 * fitnessCmp + column;
    // Get the direction from the direction table.
    int value = standardDirectionTable_[index];

    if (value > 1) {

        if (state->getRandomizer()->getRandomInteger(2) == 0)
            return 1;
        else
            return -1;

    } else {

        return value;

    }
}

double QuantumRotationGate::getRotation(double fitX, double fitB) {
    return rotationL_ + (rotationH_ - rotationL_) *
                        abs(fitX - fitB) / max(fitX, fitB);
}
