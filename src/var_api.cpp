#include <var_api.h>

namespace dio
{
    Node Variable(std::vector<int>shape, std::string initializer, 
        std::vector<double>init_args)
    {
        return Node(new variable(shape, initializer, init_args));
    }
}