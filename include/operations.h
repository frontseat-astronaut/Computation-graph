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

    class add: public operation
    {
        public:
            double run(std::vector<double>&op_arg);
            
            double partial_diff_run(std::vector<double>&op_arg, int var_idx);
    };

    class multiply: public operation
    {
        public:
            double run(std::vector<double>&op_arg);
            
            double partial_diff_run(std::vector<double>&op_arg, int var_idx);
    };

    class divide: public operation
    {
        public:
            double run(std::vector<double>&op_arg);
            
            double partial_diff_run(std::vector<double>&op_arg, int var_idx);
    };
}

#endif