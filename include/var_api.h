#ifndef __VARAPI_H_INCLUDED__   
#define __VARAPI_H_INCLUDED__  

#include<string>
#include<memory>

#include "number.h"
#include "variables.h"

namespace dio 
{
    using Number = std::shared_ptr<hidden::number>;

    Number IndependentVariable();
    Number DependentVariable();
    Number Constant(double);

    void assign(Number, double);
    double value(Number);
    double gradient(Number, Number);
}

#endif