#ifndef __VARAPI_H_INCLUDED__   
#define __VARAPI_H_INCLUDED__  

#include<string>
#include<memory>

#include "variable.h"

namespace dio 
{
    using Node = std::shared_ptr<array>;

    Node Variable(std::vector<int>shape, std::string initializer, 
        std::vector<double>init_args=std::vector<double>{})
    {
        return Node(new variable(shape, initializer, init_args));
    }

    template<typename T>
    Node Variable(T a)
    {
        return Node(new variable(a));
    }

    template<typename T>
    Node Constant(T a)
    {
        return Node(new constant(a));
    }
}

#endif