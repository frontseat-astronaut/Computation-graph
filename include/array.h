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

namespace dio
{
    class array: public node
    {
        protected:
            int get_real_index(std::vector<int> vidx);
            std::vector<int> get_virtual_index(int ridx);
            std::vector<std::shared_ptr<number>>arr;
            bool is_init;

        public:
            std::vector<int>shape;

            array(std::vector<int>shape);

            std::shared_ptr<number> get(std::vector<int>vidx);

            double get_value(std::vector<int>vidx);

            std::vector<double> get_gradient(std::shared_ptr<number>);

            std::shared_ptr<number> frobenius_norm();
    };
}

#endif