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
    class array
    {
        protected:
            int get_real_index(std::vector<int> vidx);
            std::vector<int> get_virtual_index(int ridx);
            std::vector<std::shared_ptr<number>>arr;
            std::vector<int>shape;
            
            template<typename T>
            void assign(std::vector<T>&a, int d)
            {
                if(shape.size()==d-1)
                    shape.push_back(a.size());
                
                if(shape[d-1] != a.size())
                    throw NotAGrid();

                for(int i=0; i<a.size(); ++i)
                {
                    assign(a[i], d+1);
                }
            }

            void assign(std::shared_ptr<number>&x, int d)
            {
                if(d == 1)
                    shape.push_back(1);

                arr.push_back(x);
            } 

            void assign(double&x, int d)
            {
                if(d == 1)
                    shape.push_back(1);

                arr.push_back(std::shared_ptr<number>(new constant_number(x)));
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