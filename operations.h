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
};

class add: public operation
{
    public:
        add(string key): operation(key, "add") {}

        double run(vector<double>&opargv)
        {
            if(opargv.empty())
                throw "add operation requires at least one argument";
            
            double result = 0;
            for(auto arg: opargv)
                result += arg;
            return result;
        }
};

#endif