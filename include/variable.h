#ifndef __VARIABLE_H_INCLUDED__   
#define __VARIABLE_H_INCLUDED__  

#include <string>
#include <vector>
#include <stdio.h>
#include <assert.h>

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

            constant(std::vector<int>shape, double x);

            constant(std::vector<int>shape, std::vector<double>&a);

            void compute_value() {}

            std::vector<std::vector<double>> forward_diff(std::shared_ptr<array>&);

            std::shared_ptr<array> get_grad(std::shared_ptr<array>&x);
    };

    class variable: public array
    {
        protected:
            std::vector<std::shared_ptr<array>>op_args;
            std::shared_ptr<array_op>op;
            bool is_latent;

        public:
            variable(std::vector<int>shape, double);

            variable(std::vector<int>shape, std::string initializer, 
                     std::vector<double>init_args=std::vector<double>{});

            template<typename T>
            variable(T a)
            {
                shape = dio::get_shape(a);
                allocate();
                set_value(a);

                is_latent = false;
            }

            variable(std::vector<std::shared_ptr<array>>op_args, std::shared_ptr<array_op>op);

            void compute_value();

            std::vector<std::vector<double>> forward_diff(std::shared_ptr<array>&);

            std::shared_ptr<array> get_grad(std::shared_ptr<array>&);

    };
}

#endif