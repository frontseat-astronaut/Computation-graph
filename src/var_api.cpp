#include <var_api.h>

namespace dio
{
    Number Variable()
    {
        Number ret = Number(new variable());
        return ret;
    }

    Number Variable(double x)
    {
        Number ret = Number(new variable(x));
        return ret;
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