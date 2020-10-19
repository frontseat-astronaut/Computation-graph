#include <array_op.h>

namespace dio
{
    // element_wise_op
    void element_wise_op::assert_shape(std::vector<std::vector<int>>&shapes)
    {
        for(int i=1; i<shapes.size(); ++i)
        {
            if(shapes[i] != shapes[0]) throw ShapeMismatch();
        }
    }

    std::vector<int> element_wise_op::get_out_shape(std::vector<std::vector<int>>&shapes)
    {
        return shapes[0];
    }

    std::vector<double> element_wise_op::run(std::vector<std::vector<double>>&op_args)
    {
        assert(!op_args.empty());
        std::vector<double> ret(op_args[0].size());
        std::vector<double>number_op_args(op_args.size());
        for(int j=0; j<op_args[0].size(); ++j)
        {
            for(int i=0; i<op_args.size(); ++i)
            {
                assert(op_args[i].size() == op_args[0].size());
                number_op_args[i] = op_args[i][j];
            }
            ret[j] = op->run(number_op_args);
        }
        return ret;
    }

    std::vector<std::vector<double>> element_wise_op::partial_diff_run(std::vector<std::vector<double>>&op_args, int var_idx)
    {
        std::vector<std::vector<double>>ret(op_args[var_idx].size(), std::vector<double>(op_args[var_idx].size()));
        for(int i=0; i<ret.size(); ++i)
        {
            std::vector<double>number_op_args(op_args.size());
            for(int k=0; k<op_args.size(); ++k) number_op_args[k] = op_args[k][i];
            ret[i][i] = op->partial_diff_run(number_op_args, var_idx);
        }
        return ret;
    }

    // _matmul
    void _matmul::assert_shape(std::vector<std::vector<int>>&shapes)
    {
        if(shapes.size() != 2)
            throw WrongArgCount();
        
        if(shapes[0].size() != 2 || shapes[1].size() != 2)
            throw Expected2DMatrix();

        if(shapes[0][1] != shapes[1][0])
            throw IncompatibleMatrices();
        
        _matmul::shapes = shapes;
    }

    std::vector<int> _matmul::get_out_shape(std::vector<std::vector<int>>&shapes)
    {
        return std::vector<int>{shapes[0][0], shapes[1][1]};
    }

    std::vector<double> _matmul::run(std::vector<std::vector<double>>&op_args)
    {
        assert(op_args.size() == 2);
        std::vector<double>result(shapes[0][0]*shapes[1][1]);
        matrix_multiply(result, op_args[0], op_args[1], shapes[0][0], shapes[0][1], shapes[1][1]);
        return result;
    }

    std::vector<std::vector<double>> _matmul::partial_diff_run(std::vector<std::vector<double>>&op_args, int var_idx)
    {
        assert(op_args.size() == 2);
        std::vector<std::vector<double>>ret(shapes[0][0]*shapes[1][1], std::vector<double>(shapes[var_idx][0]*shapes[var_idx][1]));
        for(int i=0; i<shapes[0][0]; ++i)
        {
            for(int j=0; j<shapes[1][1]; ++j)
            {
                int ridx = i*shapes[1][1] + j;
                for(int k=0; k<shapes[0][1]; ++k)
                {
                    if(!var_idx)
                        ret[ridx][i*shapes[0][1] + k] = op_args[1][k*shapes[1][0] + j];
                    else
                        ret[ridx][k*shapes[1][0] + j] = op_args[0][i*shapes[0][1] + k];
                }
            }
        }
        return ret;
    }

    // indexing 
    void _index::assert_shape(std::vector<std::vector<int>>&shapes)
    {
        if(shapes.size() != 1)
            throw WrongArgCount();
        if(shapes[0].size()<idx.size())
            throw InvalidDimensionCount();
        for(int d=0; d<idx.size(); ++d)
        {
            for(int idx_d: idx[d])
            {
                if(idx_d >= shapes[0][d] || idx_d<0)
                    throw IndexOutofBounds();
            }
        }
        while(idx.size()<shapes[0].size())
        {
            int d = idx.size();
            std::vector<int>idx_d(shapes[0][d]);
            for(int i=0; i<shapes[0][d]; ++i) idx_d[i] = i;
            // sort(idx_d.begin(), idx_d.end());
            idx.push_back(idx_d);
        }
    }
    
    std::vector<int> _index::get_out_shape(std::vector<std::vector<int>>&shapes)
    {
        std::vector<int>shape_size_cache(idx.size());
        for(int i=shapes[0].size()-1, mul=1; i>=0; --i)
        {
            shape_size_cache[i] = mul;
            mul *= shapes[0][i];
        }
        res_size = 1;
        std::vector<int>out_shape;
        for(int d=0; d<idx.size(); ++d)
        {
            res_size *= idx[d].size();
            if(d>=int_idx.size() || !int_idx[d])
                out_shape.push_back(idx[d].size());
        }
        if(out_shape.empty()) out_shape.push_back(1);

        ridx_map = std::vector<int>(res_size);
        int ridx_res=0;
        map_real_indices(0, 0, ridx_res, shape_size_cache); 

        return out_shape;
    }

    void _index::map_real_indices(int d, int ridx_arg, int &ridx_res, std::vector<int>&shape_size_cache)
    {
        if(d == idx.size())
        {
            ridx_map[ridx_res++] = ridx_arg;
            return;
        }
        for(int x: idx[d])
            map_real_indices(d+1, ridx_arg+x*shape_size_cache[d], ridx_res, shape_size_cache);
    }

    std::vector<double> _index::run(std::vector<std::vector<double>>&op_args)
    {
        assert(op_args.size() == 1);
        std::vector<double>ret(res_size);
        for(int i=0; i<ret.size(); ++i) ret[i] = op_args[0][ridx_map[i]];
        return ret;
    }
    
    std::vector<std::vector<double>> _index::partial_diff_run(std::vector<std::vector<double>>&op_args, int var_idx)
    {
        assert(op_args.size() == 1);
        assert(var_idx == 0);

        std::vector<std::vector<double>>J(res_size, std::vector<double>(op_args[0].size()));
        for(int i=0; i<res_size; ++i)
            J[i][ridx_map[i]] = 1;
        
        return J;
    }

    // concat
    void _concat::assert_shape(std::vector<std::vector<int>>&shapes)
    {
        if(shapes.size()!=2)
            throw WrongArgCount();

        if(shapes[0].size() != shapes[1].size())
            throw InvalidDimensionCount();

        for(int d=0; d<shapes[0].size(); ++d)
        {
            if(d == axis) continue;
            if(shapes[0][d] != shapes[1][d])
                throw ConcatShapeMismatch();
        }

        axis_partition = shapes[0][axis];
    }

    std::vector<int> _concat::get_out_shape(std::vector<std::vector<int>>&shapes)
    {
        out_shape = shapes[0];
        out_shape[axis] += shapes[1][axis];

        res_size = 1;
        for(int d=0; d<out_shape.size(); ++d)
            res_size *= out_shape[d];

        int ridx_arg[2] = {0, 0};
        int ridx_res = 0;
        ridx_map = std::vector<std::pair<int,int>>(res_size);
        map_real_indices(0, 0, ridx_arg, ridx_res);

        return out_shape;
    }


    void _concat::map_real_indices(int d, bool arg, int ridx_arg[2], int &ridx_res)
    {
        if(d == out_shape.size()) 
        {
            ridx_map[ridx_res++] = {arg, ridx_arg[arg]++};
            return;
        }
        if(d!=axis)
            for(int i=0; i<out_shape[d]; ++i)
                map_real_indices(d+1, arg, ridx_arg, ridx_res);
        else 
        {
            for(int i=0; i<axis_partition; ++i)
                map_real_indices(d+1, 0, ridx_arg, ridx_res);
            for(int i=axis_partition; i<out_shape[axis]; ++i)
                map_real_indices(d+1, 1, ridx_arg, ridx_res);
        }
    }

    std::vector<double> _concat::run(std::vector<std::vector<double>>&op_args)
    {
        assert(op_args.size()==2);
        std::vector<double>ret(res_size);
        for(int i=0; i<res_size; ++i)
            ret[i] = op_args[ridx_map[i].first][ridx_map[i].second];
        return ret;
    }

    std::vector<std::vector<double>> _concat::partial_diff_run(std::vector<std::vector<double>>&op_args, int var_idx)
    {
        assert(op_args.size() == 2);
        assert(var_idx<2 && var_idx>=0);
        std::vector<std::vector<double>>J(res_size, std::vector<double>(op_args[var_idx].size()));

        for(int i=0; i<res_size; ++i)
        {
            if(ridx_map[i].first == var_idx)
                J[i][ridx_map[i].second] = 1;
        }
        return J;
    }

    // reshape
    void _reshape::assert_shape(std::vector<std::vector<int>>&shapes)
    {
        if(shapes.size() != 1)
            throw WrongArgCount();

        int outsz=!out_shape.empty(), insz=!shapes[0].empty();
        for(int i=0; i<shapes[0].size(); ++i) insz *= shapes[0][i];
        for(int i=0; i<out_shape.size(); ++i) outsz *= out_shape[i];
        
        if(insz != outsz)
            throw SizeMismatch();
    }

    std::vector<double> _reshape::run(std::vector<std::vector<double>>&op_args)
    {
        assert(op_args.size() == 1);
        return op_args[0];
    }

    std::vector<std::vector<double>> _reshape::partial_diff_run(std::vector<std::vector<double>>&op_args, int var_idx)
    {
        assert(op_args.size() == 1);
        assert(var_idx==0);
        std::vector<std::vector<double>> J(op_args[0].size(), std::vector<double>(op_args[0].size()));
        for(int i=0; i<op_args[0].size(); ++i) J[i][i] = 1;
        return J;
    }
}