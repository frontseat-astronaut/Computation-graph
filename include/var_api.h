#ifndef __VARAPI_H_INCLUDED__   
#define __VARAPI_H_INCLUDED__  

#include<string>
#include<memory>

#include "variable.h"

namespace dio 
{
    class Node
    {
        private:
            std::shared_ptr<array> arr_ptr = NULL;
        
        public:
            Node() {};
            Node(std::shared_ptr<array>arr_ptr): arr_ptr{arr_ptr} {}
            Node(array *arr_ptr)
            {
                this->arr_ptr = std::shared_ptr<array>(arr_ptr);
            }

            std::shared_ptr<array> get() { return arr_ptr; }
    };

    Node Variable(std::vector<int>shape, std::string initializer, 
        std::vector<double>init_args=std::vector<double>{});

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

    double idx(Node a, std::vector<int>index);

    Node grad(Node a, Node b);

    void compute_val(Node a);

    void print_val(Node a);
}

#endif