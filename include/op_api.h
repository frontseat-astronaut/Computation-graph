#ifndef __OPAPI_H_INCLUDED__   
#define __OPAPI_H_INCLUDED__  

#include<vector>
#include<string>
#include<map>
#include<memory>

#include "operations.h"
#include "variables.h"
#include "var_api.h"

namespace dio
{
    Number add(Number, Number);
    Number multiply(Number, Number);
    Number divide(Number, Number);
    Number reciprocal(Number);
    Number minus(Number);
    Number powr(Number, Number);
    Number exp(Number);
}

#endif