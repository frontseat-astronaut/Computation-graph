#ifndef __OPTIMIZER_API_H_INCLUDED__   
#define __OPTIMIZER_API_H_INCLUDED__  

#include "node_api.h"
#include "optimizers.h"

namespace dio 
{
    typedef std::shared_ptr<optimizer> Optimizer;

    Optimizer SGD(std::vector<Node>params, double learning_rate, double momentum=0);

    void optimize(Node, Optimizer);
}

#endif