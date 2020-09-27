#ifndef __UTIL_H_INCLUDED__   
#define __UTIL_H_INCLUDED__   

#include <vector>

#include "exceptions.h"

namespace dio
{
    void get_shape(int d, double&x, std::vector<int>&shape);

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
}

#endif