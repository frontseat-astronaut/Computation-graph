#include <array_api.h>

namespace dio
{
    Array IndependentArray(std::vector<int>shape)
    {
        auto ret = Array(new array(shape));
        ret->init_independent();
        return ret;
    }
}