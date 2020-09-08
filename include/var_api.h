#ifndef __VARAPI_H_INCLUDED__   
#define __VARAPI_H_INCLUDED__  

#include<string>
#include<memory>

#include "node.h"
#include "variables.h"

namespace dio 
{
    using Node = std::shared_ptr<node>;

    Node IndependentVariable(std::string);
    Node DependentVariable(std::string);
    Node Constant(double);
    Node Constant(double, std::string key);

    std::string key(Node);
    void assign(Node, double);
    double value(Node);
    double gradient(Node, std::string);
    double gradient(Node, Node);
}

#endif