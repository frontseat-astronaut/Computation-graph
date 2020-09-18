#include <array.h>

namespace dio
{
    int array::get_real_index(std::vector<int> vidx)
    {
        assert(vidx.size() == shape.size());

        int ridx = 0;
        for(int i=0, j=arr.size(); i<shape.size(); ++i)
        {
            j /= shape[i];
            ridx += vidx[i]*j;
        }

        if(ridx >= arr.size())
            throw IndexOutofBounds();
        return ridx;
    }

    std::vector<int> array::get_virtual_index(int ridx)
    {
        if(ridx >= arr.size() || ridx<0)
            throw IndexOutofBounds();

        std::vector<int> vidx(shape.size());
        for(int i=0, j=arr.size(); i<shape.size(); ++i)
        {
            j /= shape[i];
            vidx[i] = ridx/j;
            ridx = ridx%j;
        }

        return vidx;
    }

    array::array(std::vector<int>shape): shape{shape}
    {
        int size = 1;
        for(int i=0; i<shape.size(); ++i) size *= shape[i];
        arr = std::vector<std::shared_ptr<number>>(size);
    }

    std::shared_ptr<number> array::get(std::vector<int>vidx)
    {
        return arr[get_real_index(vidx)];
    }

    double array::get_value(std::vector<int>vidx)
    {
        if(is_init)
            throw ArrayNotInitialized();

        return arr[get_real_index(vidx)]->get_value();
    }

    std::vector<double> array::get_gradient(std::shared_ptr<number>x)
    {
        std::vector<double>ret(arr.size());
        for(int i=0; i<arr.size(); ++i)
            ret[i] = arr[i]->get_gradient(x);
    }

    std::shared_ptr<number> array::frobenius_norm()
    {
        auto ret = std::shared_ptr<number>(new constant_number(0));
        for(int i=0; i<arr.size(); ++i)
            ret = add(ret, multiply(arr[i], arr[i]));
        return ret;
    }
}