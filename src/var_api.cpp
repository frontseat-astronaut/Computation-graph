#include <var_api.h>

namespace dio
{
    Number IndependentVariable()
    {
        Number ret = Number(new ind_variable());
        
        return ret;
    }

    Number DependentVariable()
    {
        return Number(new dep_variable());
    }

    Number Constant(double val)
    {
        return Number(new constant(val));
    }

    void assign(Number a, double val)
    {
        a->set_value(val);
    }

    double value(Number a)
    {
        return a->get_value();
    }

    double gradient(Number a, Number b)
    {
        return a->get_gradient(b);
    }
}