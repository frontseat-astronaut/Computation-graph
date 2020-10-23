#include <number_op.h>

namespace dio
{
    // add
    double _add::run(std::vector<double>&op_arg)
    {
        double result = 0;
        for(auto arg: op_arg)
            result += arg;
        return result;
    }

    double _add::partial_diff_run(std::vector<double>&op_arg, int var_idx)
    {
        return 1;
    }

    // multiply
    double _multiply::run(std::vector<double>&op_arg)
    {
        double result = 1;
        for(auto arg: op_arg)
            result *= arg;
        return result;
    }
    
    double _multiply::partial_diff_run(std::vector<double>&op_arg, int var_idx)
    {
        double result = 1;
        for(int i=0; i<op_arg.size(); ++i)
            if(i != var_idx) result *= op_arg[i];
        return result;
    }

    // divide
    double _divide::run(std::vector<double>&op_arg)
    {
        if(op_arg.size() != 2)
            throw "divide operation requires exactly two arguments";
        
        double result = op_arg[0] / op_arg[1];
        return result;
    }
    
    double _divide::partial_diff_run(std::vector<double>&op_arg, int var_idx)
    {
        double result = (var_idx == 0)*(1/op_arg[1]) + (var_idx == 1)*(-1/op_arg[1]/op_arg[1]);
        return result;
    }

    // unary minus
    double _minus::run(std::vector<double>&op_arg)
    {
        if(op_arg.size() != 1)
            throw "unary minus operation requires exactly one argument";
        
        double result = -op_arg[0];
        return result;
    }
    
    double _minus::partial_diff_run(std::vector<double>&op_arg, int var_idx)
    {
        return -1;
    }

    // power 
    double _powr::run(std::vector<double>&op_arg)
    {
        if(op_arg.size() != 2)
            throw "power operation requires exactly two arguments";
        
        double result = std::pow(op_arg[0], op_arg[1]);
        return result;
    }
    
    double _powr::partial_diff_run(std::vector<double>&op_arg, int var_idx)
    {
        double result = 0;
        if(var_idx == 0)
        {
            if(iszero(op_arg[1]))
                result = 0;
            else 
                result = op_arg[1]*std::pow(op_arg[0], op_arg[1]-1);
        }
        else if(var_idx == 1)
        {
            result = std::log(op_arg[0])*std::pow(op_arg[0], op_arg[1]);
        }
        
        return result;
    }

    // sigmoid 
    double _sigmoid::run(std::vector<double>&op_arg)
    {
        if(op_arg.size() != 1)
            throw "sigmoid operation requires exactly one arguments";
        
        double result = 1.0/(1 + std::exp(-op_arg[0]));
        return result;
    }
    
    double _sigmoid::partial_diff_run(std::vector<double>&op_arg, int var_idx)
    {
        double sgmd = run(op_arg);
        double result = sgmd*(1-sgmd);
        
        return result;
    }

    // natural log 
    double _log::run(std::vector<double>&op_arg)
    {
        if(op_arg.size() != 1)
            throw "log operation requires exactly one arguments";
        
        double result = std::log(op_arg[0]);
        return result;
    }
    
    double _log::partial_diff_run(std::vector<double>&op_arg, int var_idx)
    {
        double result = 1/op_arg[0];
        return result;
    }
}