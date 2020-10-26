#include <util.h>
 
namespace dio
{
    bool iszero(double a)
    {
        return fabs(a)<1e-9;
    }

    std::vector<int> range(int lim)
    {
        std::vector<int>ret(lim);
        for(int i=0; i<lim; ++i) ret[i] = i;
        return ret;
    }

    void get_shape(int d, double&x, std::vector<int>&shape)
    {
        if(d == 0)
            shape.push_back(1);
    } 

    int get_real_index(std::vector<int>vidx, std::vector<int>&shape, int size)
    {
        assert(vidx.size() == shape.size());
        
        if(size == -1)
        {
            size = !shape.empty();
            for(int d=0; d<shape.size(); ++d) size *= shape[d];
        }

        int ridx = 0;
        for(int i=0, j=size; i<shape.size(); ++i)
        {
            j /= shape[i];
            ridx += vidx[i]*j;
        }

        if(ridx >= size)
        {
            printf("%d\n", size);
            throw IndexOutofBounds();
        }
        return ridx;
    }

    std::vector<int> get_virtual_index(int ridx, std::vector<int>&shape, int size)
    {
        if(size == -1)
        {
            size = !shape.empty();
            for(int d=0; d<shape.size(); ++d) size *= shape[d];
        }

        if(ridx >= size|| ridx<0)
            throw IndexOutofBounds();

        std::vector<int> vidx(shape.size());
        for(int i=0, j=size; i<shape.size(); ++i)
        {
            j /= shape[i];
            vidx[i] = ridx/j;
            ridx = ridx%j;
        }

        return vidx;
    }

    void matrix_add(std::vector<std::vector<double>>&c, std::vector<std::vector<double>>&a, std::vector<std::vector<double>>&b)
    {
        assert(c.size() == a.size() && a.size() == b.size());
        assert(c[0].size() == a[0].size() && a[0].size() == b[0].size());
        for(int i=0; i<a.size(); ++i)
            for(int j=0; j<a[0].size(); ++j)
                c[i][j] = a[i][j] + b[i][j];
    }

    void matrix_multiply(std::vector<std::vector<double>>&c, std::vector<std::vector<double>>&a, std::vector<std::vector<double>>&b)
    {
        assert(a.size() == c.size());
        assert(a[0].size() == b.size());
        assert(c[0].size() == b[0].size());
        for(int i=0; i<c.size(); ++i)
            for(int j=0; j<c[0].size(); ++j)
            {
                c[i][j] = 0;
                for(int k=0; k<a[0].size(); ++k)
                {
                    if(iszero(a[i][k]) || iszero(b[k][j]))
                        c[i][j] += 0;
                    else 
                        c[i][j] += a[i][k]*b[k][j];
                }
            }
    }

    void matrix_multiply(std::vector<double>&c, std::vector<double>&a, std::vector<double>&b, int p, int q, int r)
    {
        assert(a.size() == p*q);
        assert(b.size() == q*r);
        assert(c.size() == p*r);
        for(int i=0; i<p; ++i)
        {
            for(int j=0; j<r; ++j)
            {
                int cidx = i*r + j;
                c[cidx] = 0;
                for(int k=0; k<q; ++k)
                {
                    if(iszero(a[i*q + k]) || iszero(b[k*r + j]))
                        c[cidx] += 0;
                    else 
                        c[cidx] += a[i*q + k]*b[k*r + j];
                }
            }
        }
    }
}
