#ifndef __NUMBER_OP_H_INCLUDED__   
#define __NUMBER_OP_H_INCLUDED__  

#include<vector>
#include<iostream>
#include<cmath>

#include "exceptions.h"

namespace dio
{
    class number_op
    {
        public:
            virtual double run(std::vector<double>&op_arg) = 0;
            virtual double partial_diff_run(std::vector<double>&op_arg, int var_idx) = 0;
    };

    class _add: public number_op
    {
        public:
            double run(std::vector<double>&op_arg);
            
            double partial_diff_run(std::vector<double>&op_arg, int var_idx);
    };

    class _multiply: public number_op
    {
        public:
            double run(std::vector<double>&op_arg);
            
            double partial_diff_run(std::vector<double>&op_arg, int var_idx);
    };

    class _divide: public number_op
    {
        public:
            double run(std::vector<double>&op_arg);
            
            double partial_diff_run(std::vector<double>&op_arg, int var_idx);
    };

    class _minus: public number_op 
    {
        public:
            double run(std::vector<double>&op_arg);

            double partial_diff_run(std::vector<double>&op_arg, int var_idx);
    };

    class _powr: public number_op 
    {
        public:
            double run(std::vector<double>&op_arg);

            double partial_diff_run(std::vector<double>&op_arg, int var_idx);
    };

    class _log: public number_op 
    {
        public:
            double run(std::vector<double>&op_arg);

            double partial_diff_run(std::vector<double>&op_arg, int var_idx);
    };

    class _sigmoid: public number_op 
    {
        public:
            double run(std::vector<double>&op_arg);

            double partial_diff_run(std::vector<double>&op_arg, int var_idx);
    };

    class _relu: public number_op 
    {
        public:
            double run(std::vector<double>&op_arg);

            double partial_diff_run(std::vector<double>&op_arg, int var_idx);
    };
}

#endif