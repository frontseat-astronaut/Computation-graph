#include <array.h>

namespace dio
{
    int array::get_real_index(std::vector<int> vidx)
    {
        assert(vidx.size() == shape.size());

        int ridx = 0;
        for(int i=0, j=value.size(); i<shape.size(); ++i)
        {
            j /= shape[i];
            ridx += vidx[i]*j;
        }

        if(ridx >= value.size())
            throw IndexOutofBounds();
        return ridx;
    }

    std::vector<int> array::get_virtual_index(int ridx)
    {
        if(ridx >= value.size() || ridx<0)
            throw IndexOutofBounds();

        std::vector<int> vidx(shape.size());
        for(int i=0, j=value.size(); i<shape.size(); ++i)
        {
            j /= shape[i];
            vidx[i] = ridx/j;
            ridx = ridx%j;
        }

        return vidx;
    }

    void array::allocate()
    {
        size = 1;
        for(int axis=0; axis<shape.size(); ++axis)
            size *= shape[axis];
        value = std::vector<double>(size);
        is_allocated = true;
    }

    void array::initialize(std::string&init_str, std::vector<double>&init_args)
    {
        std::shared_ptr<initializer>init;

        if(init_str == "zeros")
            init = std::shared_ptr<initializer>(new ZerosInitializer());
        else if(init_str == "gaussian" || init_str == "normal")
        {
            double mean, variance;
            if(init_args.size()<2)
                mean = 0, variance = 1;
            else 
                mean = init_args[0], variance = init_args[1];
            init = std::shared_ptr<initializer>(new GaussianInitializer(mean, variance));
        }
        else 
            return;

        init->initialize(value);
    }    

    std::vector<int> array::get_shape()
    {
        return shape;
    }

    double array::get_value(std::vector<int>vidx)
    {
        return value[get_real_index(vidx)];
    }

    void array::print()
    {
        for(int i=0; i<value.size(); ++i) printf("%lf ", value[i]);
        printf("\n");
    }
}