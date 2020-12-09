#include <variable.h>

namespace dio
{
    // constant
    constant::constant(std::vector<int>shape, double x)
    {
        array::shape = shape;
        allocate(x);
    }

    constant::constant(std::vector<int>shape, std::vector<double>&a)
    {
        array::shape = shape;
        array::value = a;
    }

    void constant::forward_diff(std::vector<std::vector<double>>&Jzx, std::shared_ptr<array>&x)
    {
        Jzx = std::vector<std::vector<double>>(size, std::vector<double>(x->get_size(), 0.0));
    }

    std::shared_ptr<array> constant::get_grad(std::shared_ptr<array>x)
    {
        throw NoGradForConstant();
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
        op->assert_shape(shapes);
        shape = op->get_out_shape(shapes);
        allocate();

        is_latent = true;
        compute_value();
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
            // printf("computing value of %lld: \n", this);
            // for(auto arg: op_arg_val)
            // {
            //     for(auto argi: arg)
            //         printf("%lf ", argi);
            //     printf("\n");
            // }
            // printf("\n");
            value = op->run(op_arg_val);
        }
    }

    void variable::update_value(std::shared_ptr<array>a)
    {
        if(is_latent)
            throw IsLatent();
        
        auto a_val = a->get_value();
        if(a_val.size() != value.size())
            throw SizeMismatch();
        value = a_val;
    }
    
    void variable::forward_diff(std::vector<std::vector<double>>&Jzx, std::shared_ptr<array>&x)
    {
        int n = x->get_size();
        int m = size;
        Jzx = std::vector<std::vector<double>>(m, std::vector<double>(n, 0.0)); // Jzx shape: (m, n)
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

                std::vector<std::vector<double>> Jyx;
                op_args[k]->forward_diff(Jyx, x);

                assert(Jyx.size() == p && Jyx[0].size() == n); // Jyx shape: (p, n)

                std::vector<std::vector<double>> temp(m, std::vector<double>(n));
                matrix_multiply(temp, Jzy, Jyx);
                std::vector<std::vector<double>> temp2 = Jzx;
                matrix_add(Jzx, temp2, temp);
            }
        }
        else
        {
            if(x.get() == this)
            {
                assert(m==n);
                for(int i=0; i<n; ++i) Jzx[i][i] = 1;
            }
        }
        // return Jzx;
    }

    std::shared_ptr<array> variable::get_grad(std::shared_ptr<array>x)
    {
        compute_value();
        std::vector<int>new_shape = shape;
        std::vector<int>x_shape = x->get_shape();
        new_shape.insert(new_shape.end(), x_shape.begin(), x_shape.end());
        std::vector<std::vector<double>> J;
        forward_diff(J, x);
        std::vector<double>grad;
        for(int i=0; i<J.size(); ++i)
            grad.insert(grad.end(), J[i].begin(), J[i].end());
        return std::shared_ptr<array>(new constant(new_shape, grad));
    }
}