#include <array.h>

namespace dio
{
    int Array::get_real_index(std::vector<int> &vidx)
    {
        assert(vidx.size() == shape.size());

        int ridx = 0;
        for(int i=0, j=arr.size(); i<shape.size(); ++i)
        {
            j /= shape[i];
            ridx += vidx[i]*j;
        }

        return ridx;
    }

    std::vector<int> Array::get_virtual_index(int ridx)
    {
        assert(ridx>=0 && ridx<arr.size());

        std::vector<int> vidx(shape.size());
        for(int i=0, j=arr.size(); i<shape.size(); ++i)
        {
            j /= shape[i];
            vidx[i] = ridx/j;
            ridx = ridx%j;
        }

        return vidx;
    }

    Array::Array(std::vector<int>shape): shape{shape}
    {
        int size = 1;
        for(int i=0; i<shape.size(); ++i) size *= shape[i];
        arr = std::vector<std::shared_ptr<number>>(size);
    }

    std::shared_ptr<number> Array::get(std::vector<int>vidx)
    {
        return arr[get_real_index(vidx)];
    }

    std::vector<double> Array::get_value()
    {
        std::vector<double>ret(arr.size());
        for(int i=0; i<arr.size(); ++i)
            ret[i] = arr[i]->get_value();
    }

    std::vector<double> Array::get_gradient(std::shared_ptr<number>x)
    {
        std::vector<double>ret(arr.size());
        for(int i=0; i<arr.size(); ++i)
            ret[i] = arr[i]->get_gradient(x);
    }

    std::shared_ptr<number> Array::frobenius_norm()
    {
        auto ret = std::shared_ptr<number>(new constant(0));
        for(int i=0; i<arr.size(); ++i)
            ret = add(ret, multiply(arr[i], arr[i]));
        return ret;
    }
}