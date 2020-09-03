#ifndef __OPERATIONS_H_INCLUDED__   
#define __OPERATIONS_H_INCLUDED__  

#include<vector>

#include "base.h"
using namespace std;

class operation: public base
{
    protected:
        string op;

    public:
        operation(string key, string op): op{op}, base("op_" + op + '_' + key) {}
        
        string get_op_name() { return op;};

        virtual double run(vector<double>&op_arg) = 0;
        virtual double partial_diff_run(vector<double>&op_arg, int var_idx) = 0;
};

class add: public operation
{
    public:
        add(string key): operation(key, "add") {}

        double run(vector<double>&op_arg)
        {
            if(op_arg.size() < 2)
                throw "add operation requires at least two arguments";
            
            double result = 0;
            for(auto arg: op_arg)
                result += arg;
            return result;
        }
        
        double partial_diff_run(vector<double>&op_arg, int var_idx)
        {
            return 1;
        }
};

class multiply: public operation
{
    public:
        multiply(string key): operation(key, "multiply") {}

        double run(vector<double>&op_arg)
        {
            if(op_arg.size() < 2)
                throw "multiply operation requires at least two arguments";
            
            double result = 1;
            for(auto arg: op_arg)
                result *= arg;
            return result;
        }
        
        double partial_diff_run(vector<double>&op_arg, int var_idx)
        {
            double result = 1;
            for(int i=0; i<op_arg.size(); ++i)
                if(i != var_idx) result *= op_arg[i];
            return result;
        }
};

class divide: public operation
{
    public:
        divide(string key): operation(key, "divide") {}

        double run(vector<double>&op_arg)
        {
            if(op_arg.size() != 2)
                throw "divide operation requires exactly two arguments";
            
            double result = op_arg[0] / op_arg[1];
            return result;
        }
        
        double partial_diff_run(vector<double>&op_arg, int var_idx)
        {
            double result = (var_idx == 0)*(1/op_arg[1]) + (var_idx == 1)*(-1/op_arg[1]/op_arg[1]);
            return result;
        }
};

#endif