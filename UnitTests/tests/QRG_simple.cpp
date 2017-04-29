//
// Created by lirfu on 27.04.17..
//

#include "../TestFrame.h"

int main() {
    TestFrame *f = new TestFrame;
    StateP state = f->getState();

    QuantumRotationGate *gate = new QuantumRotationGate(0.5 / M_PI, 1 / M_PI);

    f->testEquals("Rotation", gate->getRotation(5, 10), 0.75);

    f->testEquals("Direction (positive dir)", gate->getDirection(state, 0, 1, sqrt(2) / 2, sqrt(2) / 2), 1);
    f->testEquals("Direction (negative dir)", gate->getDirection(state, 1, 0, sqrt(2) / 2, sqrt(2) / 2), -1);
    f->testEquals("Direction (both 0)", gate->getDirection(state, 0, 0, sqrt(2) / 2, sqrt(2) / 2), 0);
    f->testEquals("Direction (both 1)", gate->getDirection(state, 1, 1, sqrt(2) / 2, sqrt(2) / 2), 0);

    f->testDiffers("Random direction (a==0)", gate->getDirection(state, 0, 1, 0, 1), 0);
    f->testDiffers("Random direction (b==0)", gate->getDirection(state, 1, 0, 1, 0), 0);

    return 0;
}