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
    template<typename T>
    void get_shape(int d, std::vector<T>&a, std::vector<int>&shape)
    {
        if(shape.size()==d-1)
            shape.push_back(a.size());
        
        if(shape[d-1] != a.size())
            throw NotAGrid();

        for(int i=0; i<a.size(); ++i)
        {
            get_shape(d+1, a[i], shape);
        }
    }

    void get_shape(int d, double&x, std::vector<int>&shape)
    {
        if(d == 1)
            shape.push_back(1);
    } 

    class array
    {
        protected:
            int get_real_index(std::vector<int> vidx);
            std::vector<int> get_virtual_index(int ridx);
            std::vector<std::shared_ptr<number>>arr;
            std::vector<int>shape;

            void allocate(number_enum num_type);
            
            void initialize(std::string&, std::vector<double>&);

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