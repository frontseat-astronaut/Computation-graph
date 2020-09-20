#ifndef __VARIABLE_H_INCLUDED__   
#define __VARIABLE_H_INCLUDED__  

#include <string>
#include <vector>

#include "array.h"
#include "node.h"
#include "exceptions.h"

namespace dio
{
    void get_shape(int d, double&x, std::vector<int>&shape)
    {
        if(d == 0)
            shape.push_back(1);
    } 

    template<typename T>
    void get_shape(int d, std::vector<T>&a, std::vector<int>&shape)
    {
        if(shape.size()==d)
            shape.push_back(a.size());
        
        if(shape[d] != a.size())
            throw NotAGrid();

        for(int i=0; i<a.size(); ++i)
        {
            get_shape(d+1, a[i], shape);
        }
    }

    template<typename T>
    std::vector<int> get_shape(T&a)
    {
        std::vector<int>shape;
        get_shape(0, a, shape);
        return shape;
    }

    class constant: public array, public node
    {
        public:
            template<typename T>
            constant(T a, std::string name="")
            {
                set_name(name);
                shape = dio::get_shape(a);
                allocate(number_enum::CONSTANT);
                assign(a);
            }
    };

    class variable: public array, public node 
    {
        public:
            variable(std::vector<int>shape, std::string initializer, 
                std::vector<double>init_args=std::vector<double>{}, std::string name="")
            {
                array::shape = shape;
                allocate(number_enum::VARIABLE);
                initialize(initializer, init_args);
                set_name(name);
            }
    };
}

#endif