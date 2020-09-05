#ifndef __VARAPI_H_INCLUDED__   
#define __VARAPI_H_INCLUDED__  

#include<string>

#include "node.h"
#include "variables.h"

namespace dio 
{
    typedef node* Node;

    Node IndependentVariable(std::string);
    Node DependentVariable(std::string);
    Node Constant(double, std::string key = "");

    void assign(Node, double);
    double value(Node);
    double gradient(Node, std::string);
    double gradient(Node, Node);
}

#endif