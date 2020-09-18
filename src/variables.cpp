#include <variables.h>
#include<iostream>
#include<exceptions.h>

namespace dio
{
    // constant_number
    double constant_number::get_gradient(std::shared_ptr<number>x)
    {
        return 0;
    }

    // variable_number
    void variable_number::assign(std::vector<std::shared_ptr<number>>opargv, std::shared_ptr<operation>op)
    {
        variable_number::opargv = opargv;
        variable_number::op = op;
        is_assigned = 1;
    }

    double variable_number::get_value()
    {
        if(!is_assigned)
            throw NotAssignedError();
        // if(is_valid) return value;

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
        if(!is_assigned)
            throw NotAssignedError();

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
        is_assigned = 0;
        value = 0;
        opargv = std::vector<std::shared_ptr<number>>();
        op = NULL;
    }
}