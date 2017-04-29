//
// Created by lirfu on 29.04.17..
//

#include "../TestFrame.h"

int main() {
    char *pars = "parameters.txt";
    TestFrame *f = new TestFrame;

    StateP state = f->getState();

    FunctionMinEvalOpP fun(new FunctionMinEvalOp);
    state->setEvalOp(fun);

    state->initialize(1, &pars);

    return 0;
}