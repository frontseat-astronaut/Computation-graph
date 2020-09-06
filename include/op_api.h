#ifndef __OPAPI_H_INCLUDED__   
#define __OPAPI_H_INCLUDED__  

#include<vector>
#include<string>
#include<map>

#include "operations.h"
#include "variables.h"
#include "var_api.h"

namespace dio
{
    Node add(Node, Node, std::string key = "");
    Node multiply(Node, Node, std::string key = "");
    Node divide(Node, Node, std::string key = "");
    Node reciprocal(Node, std::string key = "");
    Node minus(Node, std::string key = "");
    Node powr(Node, Node, std::string key = "");
    Node exp(Node, std::string key = "");
}

#endif