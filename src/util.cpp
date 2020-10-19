#include <util.h>
 
namespace dio
{
    bool iszero(double a)
    {
        return fabs(a)<1e-9;
    }

    void get_shape(int d, double&x, std::vector<int>&shape)
    {
        if(d == 0)
            shape.push_back(1);
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
                        c[i][j] = 0;
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
                for(int k=0; k<q; ++k)
                {
                    if(iszero(a[i*q + k]) || iszero(b[k*q + j]))
                        c[cidx] = 0;
                    else 
                        c[cidx] += a[i*q + k]*b[k*q + j];
                }
            }
        }
    }
}
