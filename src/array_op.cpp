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

    std::vector<int> element_wise_op::out_shape(std::vector<std::vector<int>>&shapes)
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
}