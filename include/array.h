#ifndef __ARRAY_H_INCLUDED__   
#define __ARRAY_H_INCLUDED__  

#include <memory>
#include <vector>
#include <assert.h>

#include "exceptions.h"
#include "initializers.h"

namespace dio
{
    class array
    {
        protected:
            std::vector<double>value;
            std::vector<int>shape;
            int size = 0;

            bool is_allocated = 0;

            int get_real_index(std::vector<int> vidx);
            std::vector<int> get_virtual_index(int ridx);

            // set value
            template<typename T>
            void set_value(int &idx, std::vector<T>&a)
            {
                for(int i=0; i<a.size(); ++i)
                    assign(idx, a);
            }
            void set_value(int &idx, double &x)
            {
                value[idx++] = x;
            }
            template<typename T>
            void set_value(T&a)
            {
                int idx = 0;
                set_value(idx, a);
            }

            void allocate();

            void initialize(std::string&, std::vector<double>&);

            array() {}

        public:

            std::vector<int> get_shape();

            double get_value(std::vector<int>vidx);
    };
}

#endif