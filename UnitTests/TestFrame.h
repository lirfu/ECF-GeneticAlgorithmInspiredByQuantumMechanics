//
// Created by lirfu on 27.04.17..
//

#ifndef QUANTUMINSPIREDGENETICALGORITHM_TESTFRAME_H
#define QUANTUMINSPIREDGENETICALGORITHM_TESTFRAME_H

#include <iostream>
#include <vector>

#include <ecf/ECF.h>

#include "../QuantumRegister.h"
#include "../Algorithms/QIGA.h"
#include "../Operators/QuantumRotationGate.h"
#include "../Operators/MutQuantumInversion.h"
#include "../Operators/MutQuantumSwap.h"
#include "../Problems/FunctionMin/FunctionMinEvalOp.h"

using namespace std;

class TestFrame {
public:
    StateP getState() {
        StateP state(new State);

        QuantumRegisterP qreg(new QuantumRegister);
        state->addGenotype(qreg);

        QIGAP qga(new QIGA);
        state->addAlgorithm(qga);

        return state;
    }

    void throwError(string message) {
        cout << message << endl;
        exit(1);
    }

    template<typename T>
    void testEquals(string message, T result, T expect) {
        if (result != expect) {
            cout << message << " failed (" << result << " != " << expect << ")." << endl;
            exit(1);
        }
    }

    template<typename T>
    void testDiffers(string message, T result, T expect) {
        if (result == expect) {
            cout << message << " failed (" << result << " == " << expect << ")." << endl;
            exit(1);
        }
    }
};


#endif //QUANTUMINSPIREDGENETICALGORITHM_TESTFRAME_H
