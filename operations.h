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

        virtual double run(vector<double>&opargv) = 0;
        virtual double grad_run(vector<double>&op_arg, vector<double>&grad_op_arg) = 0;
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
        
        double grad_run(vector<double>&op_arg, vector<double>&grad_op_arg)
        {
            double result = 0;
            for(auto grad_arg: grad_op_arg)
                result += 1*grad_arg;
            return result;
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
        
        double grad_run(vector<double>&op_arg, vector<double>&grad_op_arg)
        {
            if(op_arg.size() != grad_op_arg.size())
                throw "multiply operation: size of grad_op_arg and op_arg should be same";

            double result = 0;
            for(int i=0; i<op_arg.size(); ++i)
            {
                double term = grad_op_arg[i];
                for(int j=0; j<op_arg.size(); ++j)
                    term *= (i != j)*op_arg[j];
                result += term;
            }
            return result;
        }
};

#endif