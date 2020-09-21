#include <variable_number.h>
#include<exceptions.h>

namespace dio
{
    // constant_number
    double constant_number::get_gradient(std::shared_ptr<number>x)
    {
        return 0;
    }

    void constant_number::set_value(double x)
    {
        value = x;
    }

    // variable_number
    void variable_number::assign(std::vector<std::shared_ptr<number>>opargv, std::shared_ptr<operation>op)
    {
        variable_number::opargv = opargv;
        variable_number::op = op;
    }

    double variable_number::get_value()
    {
        if(op == NULL)
            return value;

        std::vector<double>tmpargval(opargv.size());
        for(int i=0; i<opargv.size(); ++i)
        {
            tmpargval[i] = opargv[i]->get_value();
        }

        value = op->run(tmpargval);
        return value;
    }

    void variable_number::set_value(double x)
    {
        reset();
        value = x;
    }

    double variable_number::get_gradient(std::shared_ptr<number>x)
    {
        if(x.get() == this)
            return 1;

        if(op == NULL)
            return 0;

        std::vector<double>tmpargval(opargv.size());
        for(int i=0; i<opargv.size(); ++i)
            tmpargval[i] = opargv[i]->get_value();

        double result = 0;
        for(int i=0; i<opargv.size(); ++i)
        {
            result += op->partial_diff_run(tmpargval, i) * opargv[i]->get_gradient(x);
        }
        return result;
    }

    void variable_number::reset()
    {
        value = 0;
        opargv = std::vector<std::shared_ptr<number>>();
        op = NULL;
    }
}