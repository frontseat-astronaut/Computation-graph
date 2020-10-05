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
        assert_shape(shapes);
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
        assert_shape(shapes);
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
}