#include <util.h>
 
namespace dio
{
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
                    c[i][j] += a[i][k]*b[k][j];
            }
    }
}
