#ifndef __VARIABLE_H_INCLUDED__   
#define __VARIABLE_H_INCLUDED__  

#include <string>
#include <vector>

#include "array.h"
#include "node.h"
#include "exceptions.h"

namespace dio
{
    class constant: public array, public node
    {
        public:
            template<typename T>
            constant(T x, std::string name="")
            {
                set_name(name);
                get_shape(0, x, shape);
                allocate(number_enum::variable);
                assign(x);
            }
    };

    class variable: public array, public node 
    {
        public:
            variable(std::vector<int>shape, std::string initializer, 
                std::vector<double>init_args=std::vector<double>{}, std::string name=""):
            {
                array::shape = shape;
                allocate(number_enum::variable);
                initialize(initializer, init_args);
                set_name(name);
            }
    };
}

#endif