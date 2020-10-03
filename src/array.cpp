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

    void array::allocate(double x)
    {
        size = 1;
        for(int axis=0; axis<shape.size(); ++axis)
            size *= shape[axis];
        value = std::vector<double>(size, x);
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

    int array::get_size()
    {
        return size;
    }

    std::vector<int> array::get_shape()
    {
        return shape;
    }

    double array::get_idx_value(std::vector<int>vidx)
    {
        return value[get_real_index(vidx)];
    }

    std::vector<double> array::get_value()
    {
        return value;
    }

    void array::print()
    {
        int idx=0;
        std::string tab="";
        print(idx, 0, tab);
        printf("\n\n");
    }

    void array::print(int &idx, int d, std::string &tab)
    {
        if(d == shape.size()-1)
        {
            printf("%s[%lf", tab.c_str(), value[idx++]);
            for(int i=1; i<shape.back(); ++i)
                printf(", %lf", value[idx++]);
            printf("]");
        }
        else 
        {
            printf("%s[\n", tab.c_str());
            tab += " ";

            print(idx, d+1, tab);
            for(int i=1; i<shape[d]; ++i)
            {
                printf(",\n");
                print(idx, d+1, tab);
            }

            tab.pop_back();
            printf("\n%s]", tab.c_str());
        }
    }
}