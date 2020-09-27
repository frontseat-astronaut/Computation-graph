#ifndef _ARRAY_OP_H_INCLUDED_
#define _ARRAY_OP_H_INCLUDED_

#include <vector>
#include <memory>
#include <assert.h>

#include "number_op.h"

namespace dio
{
    class array_op
    {
        public:
            std::vector<double> virtual run(std::vector<std::vector<double>>&op_args)=0;
            std::vector<double> virtual partial_diff_run(std::vector<std::vector<double>>&op_args, int var_idx)=0;
    };

    class element_wise_op: public array_op
    {
        protected:
            std::shared_ptr<number_op> op;

        public:
            element_wise_op(std::shared_ptr<number_op>op): op{op} {}

            std::vector<double> run(std::vector<std::vector<double>>&op_args);

            std::vector<double> partial_diff_run(std::vector<std::vector<double>>&op_args, int var_idx);
    };
}

#endif