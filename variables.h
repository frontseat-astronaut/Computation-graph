#ifndef __VARIABLES_H_INCLUDED__   
#define __VARIABLES_H_INCLUDED__  

#include<vector>

#include "node.h"
using namespace std;

class constant: public node 
{
    public:
        constant(double value, string key): node(value, key) {}

        double get_gradient(string x_key)
        {
            return 0;
        }
};

class ind_variable: public node
{
    public:
        ind_variable(string key): node(key) {}

        void set_value(double value)
        {
            ind_variable::value = value;
        }

        double get_gradient(string x_key)
        {
            return key == x_key;
        }
};

class dep_variable: public node 
{
    protected:
        vector<node*>opargv;
        operation *op;
        bool is_valid = 0;
    
    public:
        dep_variable(vector<node*>opargv, operation *op, string key)
        :opargv{opargv}, op{op}, node(key) {}

        double get_value()
        {
            // if(is_valid) return value;

            vector<double>tmpargval(opargv.size());
            for(int i=0; i<opargv.size(); ++i)
                tmpargval[i] = opargv[i]->get_value();

            value = op->run(tmpargval);
            is_valid = 1;
            return value;
        }

        double get_gradient(string x_key)
        {
            vector<double>tmpargval(opargv.size());
            for(int i=0; i<opargv.size(); ++i)
                tmpargval[i] = opargv[i]->get_value();

            double result = 0;
            for(int i=0; i<opargv.size(); ++i)
            {
                result += op->partial_diff_run(tmpargval, i) * opargv[i]->get_gradient(x_key);
            }
            return result;
        }
};

#endif