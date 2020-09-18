#ifndef __VARIABLE_NUMBER_H_INCLUDED__   
#define __VARIABLE_NUMBER_H_INCLUDED__  

#include<vector>
#include<string>
#include<iostream>
#include<memory>

#include "number.h"
#include "operations.h"
#include "node.h"

namespace dio
{
    class constant_number: public number
    {
        public:
            constant_number(double value)
            {
                constant_number::value = value;
            }

            double get_gradient(std::shared_ptr<number>);
    };

    class variable_number: public number
    {
        protected:
            std::vector<std::shared_ptr<number>>opargv;
            std::shared_ptr<operation>op = NULL;
            bool is_assigned = 0;
        
        public:
            variable_number() {}

            variable_number(double x)
            {
                is_assigned = 1;
                value = x;
            }

            variable_number(std::vector<std::shared_ptr<number>>opargv, std::shared_ptr<operation>op)
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