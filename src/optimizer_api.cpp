#include <optimizer_api.h>

namespace dio 
{
    Optimizer SGD(std::vector<Node>params, double learning_rate)
    {
        std::vector<std::shared_ptr<node>>argp;
        for(auto p: params) argp.push_back(p.get());
        return Optimizer(new sgd(argp, learning_rate));
    }

    void optimize(Node y, Optimizer opt)
    {
        opt->step(y.get());
    }
}