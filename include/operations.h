#ifndef __OPERATIONS_H_INCLUDED__   
#define __OPERATIONS_H_INCLUDED__  

#include<vector>
#include<iostream>

namespace dio
{
    class operation
    {
        public:
            virtual double run(std::vector<double>&op_arg) = 0;
            virtual double partial_diff_run(std::vector<double>&op_arg, int var_idx) = 0;
    };

    class _add: public operation
    {
        public:
            double run(std::vector<double>&op_arg);
            
            double partial_diff_run(std::vector<double>&op_arg, int var_idx);
    };

    class _multiply: public operation
    {
        public:
            double run(std::vector<double>&op_arg);
            
            double partial_diff_run(std::vector<double>&op_arg, int var_idx);
    };

    class _divide: public operation
    {
        public:
            double run(std::vector<double>&op_arg);
            
            double partial_diff_run(std::vector<double>&op_arg, int var_idx);
    };

    class _minus: public operation 
    {
        public:
            double run(std::vector<double>&op_arg);

            double partial_diff_run(std::vector<double>&op_arg, int var_idx);
    };
}

#endif