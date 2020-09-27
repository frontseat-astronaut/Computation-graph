#ifndef __OPAPI_H_INCLUDED__   
#define __OPAPI_H_INCLUDED__  

#include<vector>
#include<string>
#include<map>
#include<memory>

#include "array_op.h"
#include "number_op.h"
#include "variable.h"
#include "var_api.h"

namespace dio
{
    Node add(Node, Node);
    Node multiply(Node, Node);
    Node divide(Node, Node);
    Node reciprocal(Node);
    Node minus(Node);
    Node powr(Node, Node);
    Node exp(Node);
}

#endif