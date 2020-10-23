#ifndef __OPAPI_H_INCLUDED__   
#define __OPAPI_H_INCLUDED__  

#include<vector>
#include<string>
#include<map>
#include<memory>

#include "number_op.h"
#include "var_api.h"

namespace dio
{
    Node exp(Node);

    Node matmul(Node, Node);

    Node concat(Node a, Node b, int axis=0);

    Node reshape(Node a, std::vector<int>new_shape);

    Node reduce_sum(Node a, std::vector<int>axes);
}

#endif