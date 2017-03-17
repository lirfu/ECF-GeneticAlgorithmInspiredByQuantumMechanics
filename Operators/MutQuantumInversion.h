//
// Created by lirfu on 17.03.17..
//

#ifndef QUANTUMINSPIREDGENETICALGORITHM_QUANTUMINVERSIONMUTATION_H
#define QUANTUMINSPIREDGENETICALGORITHM_QUANTUMINVERSIONMUTATION_H


#include <ecf/ECF.h>

class MutQuantumInversion : public MutationOp {
public:

    bool initialize(StateP);

    void registerParameters(StateP);

    bool mutate(GenotypeP gene);
};

typedef boost::shared_ptr<MutQuantumInversion> MutQuantumInversionP;


#endif //QUANTUMINSPIREDGENETICALGORITHM_QUANTUMINVERSIONMUTATION_H
