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

            double get_gradient(std::string x_key);
    };

    class ind_variable: public node
    {
        public:
            ind_variable(std::string key): node(key) {}

            void set_value(double value);

            double get_gradient(std::string x_key);
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

            void assign(std::vector<node*>opargv, operation *op);

            double get_value();

            double get_gradient(std::string x_key);
    };
}
#endif