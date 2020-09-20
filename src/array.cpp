#include <array.h>

namespace dio
{
    std::shared_ptr<number> new_number(number_enum num_type)
    {
        if(num_type == number_enum::constant)
            return std::shared_ptr<number>(new constant_number(0));
        if(num_type == number_enum::variable)
            return std::shared_ptr<number>(new variable_number());
    }

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

    void array::allocate(number_enum num_type)
    {
        if(shape.size() == 0)
            throw ShapeNotSpecified();
        
        int size = 1;
        for(int i=0; i<shape.size(); ++i) size *= shape[i];

        arr = std::vector<std::shared_ptr<number>>(
            size, std::shared_ptr<number>(new_number(num_type))
        );
    }

    void array::initialize(std::string&init_str, std::vector<double>&init_args)
    {
        std::shared_ptr<initializer>init;

        if(init_str == "zeros")
            init = std::shared_ptr<initializer>(new ZerosInitializer());
        else if(init_str == "gaussian")
        {
            assert(init_args.size() >=2);
            init = std::shared_ptr<initializer>(new GaussianInitializer(init_args[0], init_args[1]));
        }
    }

    std::vector<int> array::get_shape()
    {
        return shape;
    }

    std::shared_ptr<number> array::get(std::vector<int>vidx)
    {
        return arr[get_real_index(vidx)];
    }

    double array::get_value(std::vector<int>vidx)
    {
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