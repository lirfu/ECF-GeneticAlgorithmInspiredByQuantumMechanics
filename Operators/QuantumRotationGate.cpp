//
// Created by lirfu on 28.02.17..
//

#include "QuantumRotationGate.h"

QuantumRotationGate::QuantumRotationGate(double lbound, double ubound) {
    rotationL_ = lbound * M_PI;
    rotationH_ = ubound * M_PI;
}

void QuantumRotationGate::performQuantumGateRotation(StateP state, QuantumRegisterP reg, double fitnessX,
                                                     QuantumRegisterP best, double fitnessB) {
    QuantumRegister *registerX = reg.get();
    QuantumRegister *registerB = best.get();

    uint index = 0; // Thetas array iterator.
    double rotationAmount = 2 * getRotation(fitnessX, fitnessB); // Rotation angle.

    for (uint var = 0; var < registerX->variables.size(); var++)
        for (uint bit = 0; bit < registerX->variables[var].size(); bit++) {
            // Update the thetas with the new recalculated values.
            registerX->thetas_[index] = registerX->thetas_[index]
                                        + rotationAmount
                                          * getDirection(
                    state,
                    registerX->variables[var][bit],
                    registerB->variables[var][bit],
                    cos(registerX->thetas_[index] / 2),
                    sin(registerX->thetas_[index] / 2)
            );

            index++;
        }
}

int QuantumRotationGate::getDirection(StateP state, bool qi, bool bi, double a, double b) {
    double product = a * b;

    if (qi < bi) {
        // Qbit is 0 but has to be 1.

        if (product > 0)
            return 1;
        else if (product < 0)
            return -1;
        else if (a == 0)
            return 0;

    } else if (qi > bi) {
        // Qbit is 1 but must be 0.

        if (product > 0)
            return -1;
        else if (product < 0)
            return 1;
        else if (b == 0)
            return 0;

    } else {
        // Qbit matches best, no change needed.
        return 0;
    }

    // Return a random direction, can't get any worse.
    if (state->getRandomizer()->getRandomInteger(2) == 0)
        return 1;
    else
        return -1;
}

double QuantumRotationGate::getRotation(double fitX, double fitB) {
    if (max(fitX, fitB) == 0)
        return rotationH_;

    return rotationL_ + (rotationH_ - rotationL_) *
                        abs(fitX - fitB) / max(fitX, fitB);
}

