#include <variable.h>

namespace dio
{
    variable::variable(std::vector<int>shape, std::string initializer, 
                       std::vector<double>init_args)
    {
        array::shape = shape;
        allocate();
        initialize(initializer, init_args);
        is_latent = false;
    }

    variable::variable(std::vector<std::shared_ptr<array>>op_args, std::shared_ptr<array_op>op):
        op_args{op_args}, op{op}
    {
        std::vector<std::vector<int>>shapes;
        for(std::shared_ptr<array> arg: op_args)
        {
            shapes.push_back(arg->get_shape());
        }
        shape = op->out_shape(shapes);
        allocate();

        is_latent = true;
    }

    void variable::compute_value()
    {
        if(is_latent)
        {
            std::vector<std::vector<double>>op_arg_val;
            for(std::shared_ptr<array> arg: op_args)
            {
                arg->compute_value();
                op_arg_val.push_back(arg->get_value());
            }

            value = op->run(op_arg_val);
        }
    }
}