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
    Number add(Number, Number, std::string key = "");
    Number multiply(Number, Number, std::string key = "");
    Number divide(Number, Number, std::string key = "");
    Number reciprocal(Number, std::string key = "");
    Number minus(Number, std::string key = "");
    Number powr(Number, Number, std::string key = "");
    Number exp(Number, std::string key = "");
}

#endif