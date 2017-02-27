//
// Created by lirfu on 27.02.17..
//

#ifndef QUANTUMINSPIREDGENETICALGORITHM_QIGA_H
#define QUANTUMINSPIREDGENETICALGORITHM_QIGA_H

#include "ecf/ECF.h"

class QIGA : public Algorithm {
public:
    QIGA() { name_ = "QIGA"; }

};

typedef boost::shared_ptr<QIGA> QIGAP;


#endif //QUANTUMINSPIREDGENETICALGORITHM_QIGA_H
