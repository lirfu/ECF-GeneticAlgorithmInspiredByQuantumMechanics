//
// Created by lirfu on 27.02.17..
//

#include "QuantumRegister.h"

void write(XMLNode &xQuantumRegister)
{
    xQuantumRegister = XMLNode::createXMLTopNode("QuantumRegister");
//    std::stringstream sValue;
//    sValue << nDimension_;
//    xFloatingPoint.addAttribute("size", sValue.str().c_str());
//
//    sValue.str("");
//    for(uint iVar = 0; iVar < nDimension_; iVar++)
//        sValue << "\t" << realValue[iVar];
//    xFloatingPoint.addText(sValue.str().c_str());
}


void read(XMLNode& xQuantumRegister)
{
    XMLCSTR values = xQuantumRegister.getText();
    std::stringstream sValues;
    sValues << values;

//    for(uint iVar = 0; iVar < nDimension_; iVar++) {
//        sValues >> realValue[iVar];
//    }
}