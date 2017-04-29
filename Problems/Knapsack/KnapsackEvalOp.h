//
// Created by lirfu on 02.04.17..
//

#ifndef QUANTUMINSPIREDGENETICALGORITHM_KNAPSACKEVALOP_H
#define QUANTUMINSPIREDGENETICALGORITHM_KNAPSACKEVALOP_H


#include <ecf/ECF.h>

class KnapsackEvalOp : public EvaluateOp {
protected:
    StateP state_;
    double knapsackSize_;
    double punishmentFactor_;
    vector<double> itemWeights_;
    vector<double> itemProfits_;
public:
    void registerParameters(StateP);

    bool initialize(StateP);

    FitnessP evaluate(IndividualP individual);
};

typedef boost::shared_ptr<KnapsackEvalOp> KnapsackEvalOpP;

#endif //QUANTUMINSPIREDGENETICALGORITHM_KNAPSACKEVALOP_H
