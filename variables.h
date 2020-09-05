#ifndef __VARIABLES_H_INCLUDED__   
#define __VARIABLES_H_INCLUDED__  

#include<vector>
#include<string>
#include<iostream>

#include "node.h"
#include "operations.h"

namespace dio
{
    class constant: public node 
    {
        public:
            constant(double value, std::string key): node(value, key) {}

            double get_gradient(std::string x_key)
            {
                return 0;
            }
    };

    class ind_variable: public node
    {
        public:
            ind_variable(std::string key): node(key) {}

            void set_value(double value)
            {
                ind_variable::value = value;
            }

            double get_gradient(std::string x_key)
            {
                return key == x_key;
            }
    };

    class dep_variable: public node 
    {
        protected:
            std::vector<node*>opargv;
            operation *op;
            bool is_valid = 0;
            bool is_assigned = 0;
        
        public:
            dep_variable(std::string key): node(key) {}
            dep_variable(std::vector<node*>opargv, operation *op, std::string key)
            :opargv{opargv}, op{op}, node(key)
            {
                is_assigned = 1;
            }

            void assign(std::vector<node*>opargv, operation *op)
            {
                dep_variable::opargv = opargv;
                dep_variable::op = op;
                is_assigned = 1;
            }

            double get_value()
            {
                if(!is_assigned)
                    throw "Dependent Variable not assigned";
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

            double get_gradient(std::string x_key)
            {
                if(!is_assigned)
                    throw "Dependent Variable not assigned";

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
    };
}
#endif