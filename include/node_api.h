#ifndef __NODE_API_H_INCLUDED__   
#define __NODE_API_H_INCLUDED__  

#include<string>
#include<memory>

#include "node.h"

namespace dio 
{
    class Node
    {
        private:
            std::shared_ptr<node> node_ptr;
        
        public:
            Node(std::shared_ptr<node>node_ptr): node_ptr{node_ptr} {}
            Node(node *node_ptr)
            {
                this->node_ptr = std::shared_ptr<node>(node_ptr);
            }

            std::shared_ptr<node> get() { return node_ptr; }

            Node get_jacobian(Node b);
            
            void update_val(Node);
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
            Node ret_index(std::vector<bool>&, std::vector<std::vector<int>>&);

            void get_indices(std::vector<bool>&int_idx, std::vector<std::vector<int>>&idx) {}

            template<typename... Args>
            void get_indices(std::vector<bool>&int_idx, std::vector<std::vector<int>>&idx, std::vector<int>tail, Args... args)
            {   
                idx.push_back(tail);
                int_idx.push_back(0);
                get_indices(int_idx, idx, args...);
            }

            template<typename... Args>
            void get_indices(std::vector<bool>&int_idx, std::vector<std::vector<int>>&idx, int tail, Args... args)
            {
                idx.push_back(std::vector<int>{tail});
                int_idx.push_back(tail!=-1);
                get_indices(int_idx, idx, args...);
            }

            template<typename... Args>
            Node index(Args... args)
            {
                std::vector<std::vector<int>>idx;
                std::vector<bool>int_idx;
                get_indices(int_idx, idx, args...);

                return ret_index(int_idx, idx);
            }

            // in-place reshape, implementation in src/op_api.cpp
            Node reshape(std::vector<int>new_shape);
    };

    Node Variable(std::vector<int>shape, std::string initializer, 
                  std::vector<double>init_args=std::vector<double>{});

    template<typename T>
    Node Variable(T a)
    {
        return Node(new node(false, a));
    }

    template<typename T>
    Node Constant(T a)
    {
        return Node(new node(true, a));
    }
}

#endif