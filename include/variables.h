#ifndef __VARIABLES_H_INCLUDED__   
#define __VARIABLES_H_INCLUDED__  

#include<vector>
#include<string>
#include<iostream>
#include<memory>

#include "node.h"
#include "operations.h"

namespace dio
{
    class constant: public node 
    {
        public:
            constant(double value): node(std::to_string(value)) 
            {
                constant::value = value;
            }
            constant(double value, std::string key): node(key) 
            {
                constant::value = value;
            }

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
            std::vector<std::shared_ptr<node>>opargv;
            std::shared_ptr<operation>op;
            bool is_valid = 0;
            bool is_assigned = 0;
        
        public:
            dep_variable(std::string key): node(key) {}
            dep_variable(std::vector<std::shared_ptr<node>>opargv, std::shared_ptr<operation>op, std::string key)
            :opargv{opargv}, op{op}, node(key)
            {
                is_assigned = 1;
            }

            void assign(std::vector<std::shared_ptr<node>>opargv, std::shared_ptr<operation>op);

            double get_value();

            double get_gradient(std::string x_key);
    };
}
#endif