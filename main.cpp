#include <ecf/ECF.h>
#include "Algorithms/GAIQM.h"
#include "Problems/FunctionMin/FunctionMinEvalOp.h"
#include "Problems/Knapsack/KnapsackEvalOp.h"
#include "Problems/NeuralNetwork/NeuralNetwork.h"
#include "Problems/NeuralNetwork/NNErrorEvalOp.h"

int main(int argc, char **argv) {
    StateP state(new State);

//    FunctionMinEvalOpP eval(new FunctionMinEvalOp);
    KnapsackEvalOpP eval(new KnapsackEvalOp);
//    NNErrorEvalOpP eval(new NNErrorEvalOp);
    state->setEvalOp(eval);

//    NeuralNetworkP nn(new NeuralNetwork);
//    state->addGenotype(nn);

    QuantumRegisterP qreg(new QuantumRegister);
    state->addGenotype(qreg);

    GAIQMP qga(new GAIQM);
    state->addAlgorithm(qga);

    state->initialize(argc, argv);
    state->run();
}
