#include <var_api.h>

namespace dio
{
    Number IndependentVariable(std::string key)
    {
        Number ret = Number(new ind_variable(key));
        
        return ret;
    }

    Number DependentVariable(std::string key)
    {
        return Number(new dep_variable(key));
    }

    Number Constant(double val, std::string key)
    {
        return Number(new constant(val, key));
    }

    Number Constant(double val)
    {
        return Number(new constant(val));
    }

    std::string key(Number a)
    {
        return a->get_key();
    }

    void assign(Number a, double val)
    {
        a->set_value(val);
    }

    double value(Number a)
    {
        return a->get_value();
    }

    double gradient(Number a, std::string var_key)
    {
        return a->get_gradient(var_key);
    }

    double gradient(Number a, Number b)
    {
        return a->get_gradient(b->get_key());
    }
}