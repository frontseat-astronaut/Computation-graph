#ifndef __ARRAY_OP_H_INCLUDED__
#define __ARRAY_OP_H_INCLUDED__

#include <vector>
#include <memory>
#include <assert.h>

#include "number_op.h"

namespace dio
{
    class array_op
    {
        public:
            void virtual assert_shape(std::vector<std::vector<int>>&shapes)=0;
            std::vector<int> virtual out_shape(std::vector<std::vector<int>>&shapes)=0;
            std::vector<double> virtual run(std::vector<std::vector<double>>&op_args)=0;
            std::vector<double> virtual partial_diff_run(std::vector<std::vector<double>>&op_args, int var_idx)=0;
    };

    class element_wise_op: public array_op
    {
        protected:
            std::shared_ptr<number_op> op;

        public:
            element_wise_op(std::shared_ptr<number_op>op): op{op} {}

            void assert_shape(std::vector<std::vector<int>>&shapes);

            std::vector<int> out_shape(std::vector<std::vector<int>>&shapes);

            std::vector<double> run(std::vector<std::vector<double>>&op_args);

            std::vector<double> partial_diff_run(std::vector<std::vector<double>>&op_args, int var_idx);
    };
}

#endif