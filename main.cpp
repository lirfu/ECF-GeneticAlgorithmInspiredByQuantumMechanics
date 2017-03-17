#include <ecf/ECF.h>
#include "Algorithms/QIGA.h"
#include "QuantumRegister.h"
#include "FunctionMinEvalOp.h"

int main(int argc, char **argv) {
    StateP state(new State);

    FunctionMinEvalOpP eval(new FunctionMinEvalOp);
    QuantumRegisterP reg(new QuantumRegister);

    QuantumRotationGate *lookup = new QuantumRotationGate;
    QIGAP qga(new QIGA(lookup));

    state->setEvalOp(eval);
    state->addGenotype(reg);
    state->addAlgorithm(qga);

    state->initialize(argc, argv);
    state->run();


    ofstream fitness("resultsFitness.txt");

    if (fitness.is_open()) {

        for (uint i = 0; i < state->getGenerationNo(); i++) {
            double fit = state->getStats()->getStats(i).at(7);
//            Indexes:
//            stats.push_back(min_[gen]);
//            stats.push_back(max_[gen]);
//            stats.push_back(average_[gen]);
//            stats.push_back(stdDev_[gen]);
//            stats.push_back(sampleSize_[gen]);
//            stats.push_back(time_[gen]);
//            stats.push_back(evaluations_[gen]);
//            stats.push_back(lowest_);
//            stats.push_back(highest_);

            fitness << fit << "\n";
        }

    } else {
        cout << "Unable to open error file";
    }

    fitness.close();
}
