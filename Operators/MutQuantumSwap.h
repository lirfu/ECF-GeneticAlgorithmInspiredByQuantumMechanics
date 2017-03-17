//
// Created by lirfu on 17.03.17..
//

#ifndef QUANTUMINSPIREDGENETICALGORITHM_MUTQUANTUMSWAP_H
#define QUANTUMINSPIREDGENETICALGORITHM_MUTQUANTUMSWAP_H


#include <ecf/ECF.h>

class MutQuantumSwap : public MutationOp {
public:

    bool initialize(StateP);

    void registerParameters(StateP);

    bool mutate(GenotypeP gene);
};

typedef boost::shared_ptr<MutQuantumSwap> MutQuantumSwapP;

#endif //QUANTUMINSPIREDGENETICALGORITHM_MUTQUANTUMSWAP_H
