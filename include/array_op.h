#ifndef __ARRAY_OP_H_INCLUDED__
#define __ARRAY_OP_H_INCLUDED__

#include <vector>
#include <memory>
#include <assert.h>
#include <pair>

#include "number_op.h"
#include "util.h"
#include "array_op.h"

namespace dio
{
    class array_op
    {
        public:
            void virtual assert_shape(std::vector<std::vector<int>>&shapes)=0;
            std::vector<int> virtual get_out_shape(std::vector<std::vector<int>>&shapes)=0;
            std::vector<double> virtual run(std::vector<std::vector<double>>&op_args)=0;
            std::vector<std::vector<double>> virtual partial_diff_run(std::vector<std::vector<double>>&op_args, int var_idx)=0;
    };

    class element_wise_op: public array_op
    {
        protected:
            std::shared_ptr<number_op> op;

        public:
            element_wise_op(std::shared_ptr<number_op>op): op{op} {}

            void assert_shape(std::vector<std::vector<int>>&shapes);

            std::vector<int> get_out_shape(std::vector<std::vector<int>>&shapes);

            std::vector<double> run(std::vector<std::vector<double>>&op_args);

            std::vector<std::vector<double>> partial_diff_run(std::vector<std::vector<double>>&op_args, int var_idx);
    };

    class _matmul: public array_op
    {
        protected:
            std::vector<std::vector<int>> shapes;

        public:
            void assert_shape(std::vector<std::vector<int>>&shapes);

            std::vector<int> get_out_shape(std::vector<std::vector<int>>&shapes);

            std::vector<double> run(std::vector<std::vector<double>>&op_args);

            std::vector<std::vector<double>> partial_diff_run(std::vector<std::vector<double>>&op_args, int var_idx);
    };

    class index: public array_op 
    {
        protected: 
            std::vector<std::vector<int>> idx;
            int res_size=0;
            std::vector<int>ridx_map;

        public: 
            index(std::vector<std::vector<int>>&idx): idx{idx} {};

            void assert_shape(std::vector<std::vector<int>>&shapes);

            std::vector<int> get_out_shape(std::vector<std::vector<int>>&shapes);

            void map_real_indices(int d, int &ridx_arg, int &ridx_res, std::vector<int>&shape_size_cache);

            std::vector<double> run(std::vector<std::vector<double>>&op_args);

            std::vector<std::vector<double>> partial_diff_run(std::vector<std::vector<double>>&op_args, int var_idx);
    }

    class _concat: public array_op 
    {
        protected:
            int axis=0;
            int res_size=0;
            std::vector<std::pair<int,int>>ridx_map;
            int axis_partition;
            std::vector<int>out_shape;

        public:
            _concat() {}

            _concat(int axis): axis{axis} {}

            void assert_shape(std::vector<std::vector<int>>&shapes);

            std::vector<int> get_out_shape(std::vector<std::vector<int>>&shapes);

            void map_real_indices(int d, bool arg, int ridx_arg[2], int &ridx_res);

            std::vector<double> run(std::vector<std::vector<double>>&op_args);

            std::vector<std::vector<double>> partial_diff_run(std::vector<std::vector<double>>&op_args, int var_idx);
    }
}

#endif