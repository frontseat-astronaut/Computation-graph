#include <array_op.h>

namespace dio
{
    // element_wise_op
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

    std::vector<double> element_wise_op::partial_diff_run(std::vector<std::vector<double>>&op_args, int var_idx)
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
            ret[j] = op->partial_diff_run(number_op_args, var_idx);
        }
        return ret;
    }
}