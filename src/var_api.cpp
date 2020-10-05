#include <var_api.h>

namespace dio
{
    Node Variable(std::vector<int>shape, std::string initializer, 
        std::vector<double>init_args)
    {
        return Node(new variable(shape, initializer, init_args));
    }

    double idx(Node a, std::vector<int>index)
    {
        return a->get_idx_value(index);
    }

    Node grad(Node a, Node b)
    {
        return a->get_grad(b);
    }

    void compute_val(Node a)
    {
        a->compute_value();
    }

    void print_val(Node a)
    {
        a->print();
    }
}