#include <variable.h>

namespace dio
{
    // constant
    constant::constant(std::vector<int>shape, double x)
    {
        array::shape = shape;
        allocate(x);
    }

    std::vector<std::vector<double>> constant::forward_diff(std::shared_ptr<array>&x)
    {
        return std::vector<std::vector<double>>(size, std::vector<double>(x->get_size()));
    }

    // variable
    variable::variable(std::vector<int>shape, double x)
    {
        array::shape = shape;
        allocate(x);
        is_latent = false;
    }

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
    
    std::vector<std::vector<double>> variable::forward_diff(std::shared_ptr<array>&x)
    {
        int n = x->get_size();
        int m = size;
        std::vector<std::vector<double>> Jzx(m, std::vector<double>(n)); // Jzx shape: (m, n)
        if(is_latent)
        {
            std::vector<std::vector<double>>op_arg_val;
            for(std::shared_ptr<array> arg: op_args)
            {
                arg->compute_value();
                op_arg_val.push_back(arg->get_value());
            }

            for(int k=0; k<op_args.size(); ++k)
            {
                int p = op_args[k]->get_size();
                std::vector<std::vector<double>> Jzy = op->partial_diff_run(op_arg_val, k); 
                assert(Jzy.size() == m && Jzy[0].size() == p); // Jzy shape: (m, p)

                std::vector<std::vector<double>> Jyx = op_args[k]->forward_diff(x);
                assert(Jyx.size() == p && Jyx[0].size() == n); // Jyx shape: (p, n)

                std::vector<std::vector<double>> temp(m, std::vector<double>(n));
                matrix_multiply(temp, Jzy, Jyx);
                matrix_add(Jzx, Jzx, temp);
            }
        }
        else
        {
            if(x.get() == this)
            {
                for(int i=0; i<n; ++i) Jzx[i][i] = 1;
            }
        }
        return Jzx;
    }
}