#ifndef __VARAPI_H_INCLUDED__   
#define __VARAPI_H_INCLUDED__  

#include<string>
#include<memory>

#include "number.h"
#include "variables.h"

namespace dio 
{
    using Number = std::shared_ptr<number>;

    Number IndependentVariable(std::string);
    Number DependentVariable(std::string);
    Number Constant(double);
    Number Constant(double, std::string key);

    std::string key(Number);
    void assign(Number, double);
    double value(Number);
    double gradient(Number, std::string);
    double gradient(Number, Number);
}

#endif