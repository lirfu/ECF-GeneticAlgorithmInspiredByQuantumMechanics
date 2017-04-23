//
// Created by lirfu on 02.04.17..
//

#include "KnapsackEvalOp.h"

void KnapsackEvalOp::registerParameters(StateP state) {
//    EvaluateOp::registerParameters(state);

    state->getRegistry()->registerEntry("eval.knapsackSize", (voidP) (NULL), ECF::DOUBLE,
                                        "size (weight threshold) of the knapsack (mandatory).");
    state->getRegistry()->registerEntry("eval.itemsFile", (voidP) (NULL), ECF::STRING,
                                        "path to file containing items prices and weights (mandatory).");
}

bool KnapsackEvalOp::initialize(StateP state) {
//    EvaluateOp::initialize(state);
    knapsackSize_ = *(double *) state->getRegistry()->getEntry("eval.knapsackSize").get();

    string dataFilepath = *(string *) state->getRegistry()->getEntry("eval.itemsFile").get();

    // Open input stream.
    ifstream file;
    file.open(dataFilepath);

    if (file.is_open()) {
        string line;

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
//    cout << "ENTER" << endl;

    FitnessP fitness(new FitnessMax);

    double profit = 0;
    double weight = 0;

//    BinaryP gen = boost::dynamic_pointer_cast<Binary::Binary>(individual->getGenotype());
//    for (uint i = 0; i < gen->variables.size(); i++) {
//        for (uint j = 0; j < gen->variables[i].size(); j++) {
//            profit += itemProfits_[i * gen->getNumBits() + j] * gen->variables[i][j];
//            weight += itemWeights_[i * gen->getNumBits() + j] * gen->variables[i][j];
//        }
//    }

    BitStringP gen = boost::dynamic_pointer_cast<BitString::BitString>(individual->getGenotype());
    for (uint i = 0; i < gen->bits.size(); i++) {
        profit += itemProfits_[i] * gen->bits[i];
        weight += itemWeights_[i] * gen->bits[i];
    }

//     Punish overfilling.
    if (weight > knapsackSize_) {
        profit -= (weight - knapsackSize_) * 5;
    }

    fitness->setValue(profit);
    return fitness;
}