#include <variables.h>
#include<iostream>
#include<exceptions.h>

namespace dio
{
    // constant
    double constant::get_gradient(std::string x_key)
    {
        return 0;
    }

    // ind_variable
    void ind_variable::set_value(double value)
    {
        ind_variable::value = value;
    }

    double ind_variable::get_gradient(std::string x_key)
    {
        return key == x_key;
    }

    // dep_variable
    void dep_variable::assign(std::vector<std::shared_ptr<node>>opargv, std::shared_ptr<operation>op)
    {
        dep_variable::opargv = opargv;
        dep_variable::op = op;
        is_assigned = 1;
    }

    double dep_variable::get_value()
    {
        if(!is_assigned)
            throw NotAssignedError();
        // if(is_valid) return value;

        std::vector<double>tmpargval(opargv.size());
        for(int i=0; i<opargv.size(); ++i)
        {
            tmpargval[i] = opargv[i]->get_value();
        }

        value = op->run(tmpargval);
        is_valid = 1;
        return value;
    }

    double dep_variable::get_gradient(std::string x_key)
    {
        if(!is_assigned)
            throw NotAssignedError();

        std::vector<double>tmpargval(opargv.size());
        for(int i=0; i<opargv.size(); ++i)
            tmpargval[i] = opargv[i]->get_value();

        double result = 0;
        for(int i=0; i<opargv.size(); ++i)
        {
            result += op->partial_diff_run(tmpargval, i) * opargv[i]->get_gradient(x_key);
        }
        return result;
    }
}