#include "var_api.h"

namespace dio
{
    Node IndependentVariable(std::string key)
    {
        return new ind_variable(key);
    }

    Node DependentVariable(std::string key)
    {
        return new dep_variable(key);
    }

    Node Constant(double val, std::string key)
    {
        return new constant(val, key);
    }

    void assign(Node a, double val)
    {
        a->set_value(val);
    }
}