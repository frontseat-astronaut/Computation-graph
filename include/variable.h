#ifndef __VARIABLE_H_INCLUDED__   
#define __VARIABLE_H_INCLUDED__  

#include <string>
#include <vector>
#include <stdio.h>

#include "array.h"
#include "exceptions.h"
#include "array_op.h"
#include "util.h"

namespace dio
{
    class constant: public array
    {
        public:
            template<typename T>
            constant(T a)
            {
                shape = dio::get_shape(a);
                allocate();
                set_value(a);
            }
    };

    class variable: public array
    {
        protected:
            std::vector<std::shared_ptr<array>>op_args;
            std::shared_ptr<array_op>op;
            bool is_latent;

        public:
            variable(std::vector<int>shape, std::string initializer, 
                     std::vector<double>init_args=std::vector<double>{})
            {
                array::shape = shape;
                allocate();
                initialize(initializer, init_args);
                is_latent = false;
            }

            template<typename T>
            variable(T a)
            {
                shape = dio::get_shape(a);
                allocate();
                set_value(a);

                is_latent = false;
            }

            variable(std::vector<std::shared_ptr<array>>op_args, std::shared_ptr<array_op>op):
                    op_args{op_args}, op{op}
            {
                is_latent = true;
            }
    };
}

#endif