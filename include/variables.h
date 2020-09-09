#ifndef __VARIABLES_H_INCLUDED__   
#define __VARIABLES_H_INCLUDED__  

#include<vector>
#include<string>
#include<iostream>
#include<memory>

#include "number.h"
#include "operations.h"

namespace dio
{
    class constant: public number 
    {
        public:
            constant(double value): number(std::to_string(value)) 
            {
                constant::value = value;
            }
            constant(double value, std::string key): number(key) 
            {
                constant::value = value;
            }

            double get_gradient(std::string x_key);
    };

    class ind_variable: public number
    {
        public:
            ind_variable(std::string key): number(key) {}

            void set_value(double value);

            double get_gradient(std::string x_key);
    };

    class dep_variable: public number 
    {
        protected:
            std::vector<std::shared_ptr<number>>opargv;
            std::shared_ptr<operation>op;
            bool is_assigned = 0;
        
        public:
            dep_variable(std::string key): number(key) {}
            dep_variable(std::vector<std::shared_ptr<number>>opargv, std::shared_ptr<operation>op, std::string key)
            :opargv{opargv}, op{op}, number(key)
            {
                is_assigned = 1;
            }

            void assign(std::vector<std::shared_ptr<number>>opargv, std::shared_ptr<operation>op);

            double get_value();

            double get_gradient(std::string x_key);

            void reset();
    };
}
#endif