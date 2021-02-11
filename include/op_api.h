#ifndef __OPAPI_H_INCLUDED__   
#define __OPAPI_H_INCLUDED__  

#include<vector>
#include<string>
#include<map>
#include<memory>

#include "number_op.h"
#include "node_api.h"

namespace dio
{
    Node exp(Node);

    Node log(Node);

    Node sigmoid(Node);

    Node relu(Node);

    Node matmul(Node, Node);

    Node concat(Node a, Node b, int axis=0);

    Node reshape(Node a, std::vector<int>new_shape);

    Node reduce_sum(Node a, std::vector<int>axes);

    Node convolve_2D(Node x, Node kernel, std::vector<int>pad=std::vector<int>{0, 0}, std::vector<int>stride=std::vector<int>{1, 1});
}

#endif