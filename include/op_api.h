#ifndef __OPAPI_H_INCLUDED__   
#define __OPAPI_H_INCLUDED__  

#include<vector>
#include<string>
#include<map>
#include<memory>

#include "number_op.h"
#include "var_api.h"

namespace dio
{
    Node add(Node, Node);
    Node multiply(Node, Node);
    Node divide(Node, Node);
    Node reciprocal(Node);
    Node minus(Node);
    Node powr(Node, Node);
    Node exp(Node);

    Node matmul(Node, Node);

    // index operator
    // Variadic templates in C++: https://eli.thegreenplace.net/2014/variadic-templates-in-c/
    Node ret_index(Node a, std::vector<std::vector<int>>&);
    void get_indices(std::vector<std::vector<int>>&idx);
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
    Node index(Node a, Args... args)
    {
        std::vector<std::vector<int>>idx;
        get_indices(idx, args...);

        return ret_index(a, idx);
    }

    Node concat(Node a, Node b, int axis=0);
}

#endif