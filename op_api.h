#ifndef __OPAPI_H_INCLUDED__   
#define __OPAPI_H_INCLUDED__  

#include<vector>
#include<string>
#include<map>

#include "operations.h"
#include "variables.h"
#include "var_api.h"

Node Add(Node, Node, std::string key = "");
Node Multiply(Node, Node, std::string key = "");
Node Divide(Node, Node, std::string key = "");
Node Reciprocal(Node, std::string key = "");

#endif