#ifndef __NODE_OP_H_INCLUDED__
#define __NODE_OP_H_INCLUDED__

#include <vector>
#include <memory>
#include <assert.h>
#include <utility>
#include <algorithm>

#include "number_op.h"
#include "util.h"

namespace dio
{
    class node_op
    {
        public:
            void virtual assert_shape(std::vector<std::vector<int>>&shapes)=0;
            std::vector<int> virtual get_out_shape(std::vector<std::vector<int>>&shapes)=0;
            std::vector<double> virtual run(std::vector<std::vector<double>>&op_args)=0;
            std::vector<std::vector<double>> virtual partial_diff_run(std::vector<std::vector<double>>&op_args, int var_idx)=0;
    };

    class element_wise_op: public node_op
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

    class _matmul: public node_op
    {
        protected:
            std::vector<std::vector<int>> shapes;

        public:
            void assert_shape(std::vector<std::vector<int>>&shapes);

            std::vector<int> get_out_shape(std::vector<std::vector<int>>&shapes);

            std::vector<double> run(std::vector<std::vector<double>>&op_args);

            std::vector<std::vector<double>> partial_diff_run(std::vector<std::vector<double>>&op_args, int var_idx);
    };

    class _index: public node_op 
    {
        protected: 
            std::vector<std::vector<int>> idx;
            std::vector<bool>int_idx;
            int res_size=0;
            std::vector<int>ridx_map;

        public: 
            _index(std::vector<bool>&int_idx, std::vector<std::vector<int>>&idx): idx{idx}, int_idx{int_idx} {}

            void assert_shape(std::vector<std::vector<int>>&shapes);

            std::vector<int> get_out_shape(std::vector<std::vector<int>>&shapes);

            void map_real_indices(int d, int ridx_arg, int &ridx_res, std::vector<int>&shape_size_cache);

            std::vector<double> run(std::vector<std::vector<double>>&op_args);

            std::vector<std::vector<double>> partial_diff_run(std::vector<std::vector<double>>&op_args, int var_idx);
    };

    class _concat: public node_op 
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
    };

    class _reshape: public node_op
    {
        protected:
            std::vector<int>out_shape;

        public:
            _reshape(std::vector<int>&shape): out_shape(shape) {}

            void assert_shape(std::vector<std::vector<int>>&shapes);

            std::vector<int> get_out_shape(std::vector<std::vector<int>>&shapes) { return out_shape; }

            std::vector<double> run(std::vector<std::vector<double>>&op_args);

            std::vector<std::vector<double>> partial_diff_run(std::vector<std::vector<double>>&op_args, int var_idx);
    };

    class _reduce_op: public node_op
    {
        protected:
            std::shared_ptr<number_op> op;
            std::vector<std::vector<int>>ridx_map;
            std::vector<int>axes;

        public:
            _reduce_op(std::shared_ptr<number_op>op, std::vector<int>axes): op{op}, axes{axes}
            {
                std::sort(axes.begin(), axes.end());
            }

            void assert_shape(std::vector<std::vector<int>>&shapes);

            std::vector<int> get_out_shape(std::vector<std::vector<int>>&shapes);

            void map_real_indices(int d, int axes_idx, int &ridx_arg, std::vector<int>&vidx_res, std::vector<int>&res_shape,
                                  std::vector<int>&arg_shape);

            std::vector<double> run(std::vector<std::vector<double>>&op_args);

            std::vector<std::vector<double>> partial_diff_run(std::vector<std::vector<double>>&op_args, int var_idx);
    };
}
#endif