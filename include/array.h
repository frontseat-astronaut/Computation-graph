#ifndef __ARRAY_H_INCLUDED__   
#define __ARRAY_H_INCLUDED__  

#include <memory>
#include <vector>
#include <assert.h>

#include "number.h"
#include "variable_number.h"
#include "op_api.h"
#include "exceptions.h"
#include "node.h"
#include "initializers.h"

namespace dio
{
    class array
    {
        protected:
            int get_real_index(std::vector<int> vidx);
            std::vector<int> get_virtual_index(int ridx);
            std::vector<std::shared_ptr<number>>arr;
            std::vector<int>shape;

            void allocate(number_enum num_type);
            
            void initialize(std::string&, std::vector<double>&);

            void assign_recur(int &idx, double &x)
            {
                arr[idx++]->set_value(x);
            }

            template<typename T>
            void assign_recur(int &idx, std::vector<T>&a)
            {
                for(int i=0; i<a.size(); ++i)
                    assign_recur(idx, a[i]);
            }

            template<typename T>
            void assign(T&a)
            {
                int idx = 0;
                assign_recur(idx, a);
            }

            array() {}

        public:

            std::vector<int> get_shape();

            std::shared_ptr<number> get(std::vector<int>vidx);

            double get_value(std::vector<int>vidx);

            std::vector<double> get_gradient(std::shared_ptr<number>);

            std::shared_ptr<number> frobenius_norm();
    };
}

#endif