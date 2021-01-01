#ifndef __UTIL_H_INCLUDED__   
#define __UTIL_H_INCLUDED__   

#include <map>
#include <vector>
#include <assert.h>
#include <math.h>

#include "exceptions.h"

namespace dio
{
    bool iszero(double, double EPSILON=1e-6);

    std::vector<int> range(int lim);

    void get_shape(int d, double &x, std::vector<int>&shape);

    template<typename T>
    void get_shape(int d, std::vector<T> &a, std::vector<int>&shape)
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
        dio::get_shape(0, a, shape);
        return shape;
    }

    int get_real_index(std::vector<int>vidx, std::vector<int>&shape, int size=-1);

    std::vector<int> get_virtual_index(int ridx, std::vector<int>&shape, int size=-1);

    std::vector<std::vector<double>> get_identity_matrix(int n);

    void matrix_add(std::vector<std::vector<double>>&c, std::vector<std::vector<double>>&a, std::vector<std::vector<double>>&b);

    void matrix_multiply(std::vector<std::vector<double>>&c, std::vector<std::vector<double>>&a, std::vector<std::vector<double>>&b);

    void matrix_multiply(std::vector<double>&c, std::vector<double>&a, std::vector<double>&b, int p, int q, int r);

    void scale_vector(std::vector<double>&v, double lambda);

    void add_vectors(std::vector<double>&w, std::vector<double>&u, std::vector<double>&v);
}

#endif