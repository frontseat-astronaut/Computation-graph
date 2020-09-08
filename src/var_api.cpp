#include <var_api.h>

namespace dio
{
    Node IndependentVariable(std::string key)
    {
        Node ret = Node(new ind_variable(key));
        
        return ret;
    }

    Node DependentVariable(std::string key)
    {
        return Node(new dep_variable(key));
    }

    Node Constant(double val, std::string key)
    {
        return Node(new constant(val, key));
    }

    Node Constant(double val)
    {
        return Node(new constant(val));
    }

    std::string key(Node a)
    {
        return a->get_key();
    }

    void assign(Node a, double val)
    {
        a->set_value(val);
    }

    double value(Node a)
    {
        return a->get_value();
    }

    double gradient(Node a, std::string var_key)
    {
        return a->get_gradient(var_key);
    }

    double gradient(Node a, Node b)
    {
        return a->get_gradient(b->get_key());
    }
}