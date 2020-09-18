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
            constant(double value)
            {
                constant::value = value;
            }

            double get_gradient(std::shared_ptr<number>);
    };

    class variable: public number 
    {
        protected:
            std::vector<std::shared_ptr<number>>opargv;
            std::shared_ptr<operation>op = NULL;
            bool is_assigned = 0;
        
        public:
            variable() {}

            variable(double x)
            {
                is_assigned = 1;
                value = x;
            }

            variable(std::vector<std::shared_ptr<number>>opargv, std::shared_ptr<operation>op)
            :opargv{opargv}, op{op}
            {
                is_assigned = 1;
            }

            void assign(std::vector<std::shared_ptr<number>>opargv, std::shared_ptr<operation>op);

            double get_value();

            void set_value(double);

            double get_gradient(std::shared_ptr<number>);

            void reset();
    };
}
#endif