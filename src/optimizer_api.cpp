#include <optimizer_api.h>

namespace dio 
{
    Optimizer SGD(std::vector<Node>params, double learning_rate, double momentum)
    {
        std::vector<std::shared_ptr<node>>argp;
        for(auto p: params) argp.push_back(p.get());
        return Optimizer(new sgd(argp, learning_rate, momentum));
    }

    void optimize(Node y, Optimizer opt, bool do_gradient_check, double EPSILON)
    {
        opt->step(y.get(), do_gradient_check, EPSILON);
    }
}