#include <operations.h>
#include <exceptions.h>

namespace dio
{
    bool iszero(double a)
    {
        return fabs(a)<1e-9;
    }

    // add
    double _add::run(std::vector<double>&op_arg)
    {
        if(op_arg.size() != 2)
            throw "add operation requires exactly two arguments";
        
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
        if(op_arg.size() != 2)
            throw "multiply operation requires exactly two arguments";
        
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
    double _power::run(std::vector<double>&op_arg)
    {
        if(op_arg.size() != 2)
            throw "power operation requires exactly two arguments";
        
        double result = std::pow(op_arg[0], op_arg[1]);
        return result;
    }
    
    double _power::partial_diff_run(std::vector<double>&op_arg, int var_idx)
    {
        double result = 0;
        if(var_idx == 0)
            result = std::pow(op_arg[0], op_arg[1]);
        else if(var_idx == 1)
            result = std::log(op_arg[0])*std::pow(op_arg[0], op_arg[1]);
        
        return result;
    }
}