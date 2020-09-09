#ifndef __ARRAY_H_INCLUDED__   
#define __ARRAY_H_INCLUDED__  

#include <memory>
#include <vector>
#include <assert.h>

#include "number.h"
#include "variables.h"
#include "op_api.h"

namespace dio
{
    class Array
    {
        private:
            int get_real_index(std::vector<int> &vidx);
            std::vector<int> get_virtual_index(int ridx);

        protected:
            std::vector<std::shared_ptr<number>>arr;

        public:
            std::vector<int>shape;

            Array(std::vector<int> shape);

            std::shared_ptr<number> get(std::vector<int>vidx);

            std::vector<double> get_value();

            std::vector<double> get_gradient(std::shared_ptr<number>);

            std::shared_ptr<number> frobenius_norm();
    };
}

#endif