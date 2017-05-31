//
// Created by lirfu on 02.04.17..
//

#include "KnapsackEvalOp.h"
#include "../../QuantumRegister.h"

void KnapsackEvalOp::registerParameters(StateP state) {
//    EvaluateOp::registerParameters(state);

    state->getRegistry()->registerEntry("eval.knapsackSize", (voidP) (NULL), ECF::DOUBLE,
                                        "size (weight threshold) of the knapsack (mandatory).");
    state->getRegistry()->registerEntry("eval.itemsFile", (voidP) (NULL), ECF::STRING,
                                        "path to file containing items prices and weights (mandatory).");
    state->getRegistry()->registerEntry("eval.punishmentFactor", (voidP) (new double(5)), ECF::DOUBLE,
                                        "the overweight is multiplied by this constant (default: 5).");
}

bool KnapsackEvalOp::initialize(StateP state) {
//    EvaluateOp::initialize(state);
    state_ = state;
    knapsackSize_ = *(double *) state->getRegistry()->getEntry("eval.knapsackSize").get();
    punishmentFactor_ = *(double *) state->getRegistry()->getEntry("eval.punishmentFactor").get();

    string dataFilepath = *(string *) state->getRegistry()->getEntry("eval.itemsFile").get();

    // Open input stream.
    ifstream file;
    file.open(dataFilepath);

    if (file.is_open()) {
        string line;

        itemWeights_.clear();
        itemProfits_.clear();

        // For each item read and store weights and profits.
        std::vector<double> values;
        while (getline(file, line)) {

            string buffer = "";
            uint index = 0;

            // Skip spaces.
            while (isspace(line[index])) index++;

            // Skip empty lines.
            if (line.substr(index, line.length()).empty())
                continue;

            // The # character starts a line comment (skip).
            if (line[index] == '#')
                continue;

            // Read item weight.
            while (!isspace(line[index])) {
                buffer += line[index];
                index++;
            }
            // Store item weight.
            itemWeights_.push_back(stod(buffer));
            buffer = "";

            // Skip spaces.
            while (isspace(line[index])) index++;

            // Read item profit.
            while (!isspace(line[index])) {
                buffer += line[index];
                index++;
            }
            // Store item profit.
            itemProfits_.push_back(stod(buffer));
        }

        file.close();
    } else {
        return false;
    }

    //FIXME testing
//    for(uint i=0; i<itemProfits_.size(); i++)
//        cout<<"Item "<<i<<" weights "<<itemWeights_[i]<<" and has profit "<<itemProfits_[i]<<endl;

    return true;
}


FitnessP KnapsackEvalOp::evaluate(IndividualP individual) {
    FitnessP fitness(new FitnessMax);

    double profit = 0;
    double weight = 0;

    vector<bool> bitstring = boost::dynamic_pointer_cast<BitString::BitString>(individual->getGenotype())->bits;

    for (uint i = 0; i < itemWeights_.size(); i++) {
        profit += itemProfits_[i] * bitstring[i];
        weight += itemWeights_[i] * bitstring[i];
    }

//     Punish overfilling.
    if (weight > knapsackSize_)
        profit -= (weight - knapsackSize_) * punishmentFactor_;

//  Repair overfilling.
//    int i;
//    while (weight > knapsackSize_) {
//        i = state_->getRandomizer()->getRandomInteger((int) (itemWeights_.size())); // Select a random item index.
//
//        while (bitstring[i]==0) // If item is not selected, find next index with item selected.
//            i = (int) ((i+1) % bitstring.size());
//
//        bitstring[i] = 0;
//        profit -= itemProfits_[i];
//        weight -= itemWeights_[i];
//    }

//    cout<<profit<<" ";
//    boost::dynamic_pointer_cast<QuantumRegister>(individual->getGenotype(1))->printOut();
//    cout<<endl;

    fitness->setValue(profit);
    return fitness;
}