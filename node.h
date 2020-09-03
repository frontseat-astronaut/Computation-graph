#ifndef __NODE_H_INCLUDED__   
#define __NODE_H_INCLUDED__  

#include "base.h"
using namespace std;

class node: public base
{
    protected:
        double value = 0;

    public:
        node(string key):base(key) {}
        node(double value, string key): value{value}, base(key) {}

        double get_value()
        {
            return value;
        }

        virtual double get_gradient(string x_key) = 0;
};

#endif