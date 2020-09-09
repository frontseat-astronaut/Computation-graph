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
    namespace hidden
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

        class ind_variable: public number
        {
            public:
                void set_value(double value);

                double get_gradient(std::shared_ptr<number>);
        };

        class dep_variable: public number 
        {
            protected:
                std::vector<std::shared_ptr<number>>opargv;
                std::shared_ptr<operation>op;
                bool is_assigned = 0;
            
            public:
                dep_variable() {}
                dep_variable(std::vector<std::shared_ptr<number>>opargv, std::shared_ptr<operation>op)
                :opargv{opargv}, op{op}
                {
                    is_assigned = 1;
                }

                void assign(std::vector<std::shared_ptr<number>>opargv, std::shared_ptr<operation>op);

                double get_value();

                double get_gradient(std::shared_ptr<number>);

                void reset();
        };
    }
}
#endif