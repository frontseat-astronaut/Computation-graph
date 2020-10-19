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

            Node grad(Node b);
            
            void compute_val(); 
            void print_val();

            double val_at_index(std::vector<int>index);

            // implementations in src/op_api.cpp
            Node operator+(Node other);
            friend Node operator+(double a, Node b);
            friend Node operator+(Node a, double b);

            Node operator*(Node other);
            friend Node operator*(double a, Node b);
            friend Node operator*(Node a, double b);

            Node operator/(Node other);
            friend Node operator/(double a, Node b);
            friend Node operator/(Node a, double b);

            Node operator-(Node other);
            friend Node operator-(double a, Node b);
            friend Node operator-(Node a, double b);

            Node operator-();

            Node operator^(Node other);
            friend Node operator^(double a, Node b);
            friend Node operator^(Node a, double b);

            // index operator, implementation in src/op_api.cpp
            // Variadic templates in C++: https://eli.thegreenplace.net/2014/variadic-templates-in-c/
            Node ret_index(std::vector<std::vector<int>>&);
            void get_indices(std::vector<std::vector<int>>&idx) {}
            template<typename... Args>
            void get_indices(std::vector<std::vector<int>>&idx, std::vector<int>tail, Args... args)
            {
                idx.push_back(tail);
                get_indices(idx, args...);
            }
            template<typename... Args>
            void get_indices(std::vector<std::vector<int>>&idx, int tail, Args... args)
            {
                idx.push_back(std::vector<int>{tail});
                get_indices(idx, args...);
            }
            template<typename... Args>
            Node index(Args... args)
            {
                std::vector<std::vector<int>>idx;
                get_indices(idx, args...);

                return ret_index(idx);
            }
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

}

#endif