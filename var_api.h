#ifndef __VARAPI_H_INCLUDED__   
#define __VARAPI_H_INCLUDED__  

#include<string>

#include "node.h"
#include "variables.h"

typedef node* Node;

Node IndependentVariable(std::string);
Node DependentVariable(std::string);
Node Constant(double, std::string key = "");

#endif