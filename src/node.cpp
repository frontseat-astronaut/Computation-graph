#include <node.h>

namespace dio
{
    void node::allocate(double x)
    {
        size = !shape.empty();
        for(int axis=0; axis<shape.size(); ++axis)
            size *= shape[axis];
        value = std::vector<double>(size, x);
        is_allocated = true;
    }

    void node::initialize(std::string&init_str, std::vector<double>&init_args)
    {
        std::shared_ptr<initializer>init;

        if(init_str == "zeros")
            init = std::shared_ptr<initializer>(new ZerosInitializer());
        else if(init_str == "gaussian" || init_str == "normal")
        {
            double mean, variance;
            if(init_args.size()<2)
                mean = 0, variance = 1;
            else 
                mean = init_args[0], variance = init_args[1];
            init = std::shared_ptr<initializer>(new GaussianInitializer(mean, variance));
        }
        else 
            return;

        init->initialize(value);
    }    

    int node::get_size()
    {
        return size;
    }

    std::vector<int> node::get_shape()
    {
        return shape;
    }

    double node::get_idx_value(std::vector<int>vidx)
    {
        return value[get_real_index(vidx, shape, size)];
    }

    std::vector<double> node::get_value()
    {
        return value;
    }

    void node::print()
    {
        int idx=0;
        std::string tab="";
        print(idx, 0, tab);
    }

    void node::print(int &idx, int d, std::string &tab)
    {
        if(d == shape.size()-1)
        {
            printf("%s[%lf", tab.c_str(), value[idx++]);
            for(int i=1; i<shape[d]; ++i)
                printf(", %lf", value[idx++]);
            printf("]");
        }
        else 
        {
            printf("%s[\n", tab.c_str());
            tab += " ";

            print(idx, d+1, tab);
            for(int i=1; i<shape[d]; ++i)
            {
                printf(",\n");
                print(idx, d+1, tab);
            }

            tab.pop_back();
            printf("\n%s]", tab.c_str());
        }
    }

    void node::_change_shape(std::vector<int>&new_shape)
    {
        int new_size = !new_shape.empty();
        for(int i=0; i<new_shape.size(); ++i)
            new_size *= new_shape[i];
        
        if(new_size!=size)
        {
            printf("%d %d\n", new_size, size);
            throw SizeMismatch();
        }
        
        shape = new_shape;
    }

    node::node(bool is_constant, std::vector<int>shape, std::vector<double>&a)
    {
        node::shape = shape;
        value = a;
        is_latent = false;
        node::is_constant = is_constant;
    }

    node::node(bool is_constant, std::vector<int>shape, double x)
    {
        node::shape = shape;
        allocate(x);
        is_latent = false;
        node::is_constant = is_constant;
    }

    node::node(std::vector<int>shape, std::string initializer, 
               std::vector<double>init_args)
    {
        node::shape = shape;
        allocate();
        initialize(initializer, init_args);
        is_latent = false;
        is_constant = false;
    }

    node::node(std::vector<std::shared_ptr<node>>op_args, std::shared_ptr<node_op>op):
        op_args{op_args}, op{op}
    {
        std::vector<std::vector<int>>shapes;
        for(std::shared_ptr<node> arg: op_args)
        {
            shapes.push_back(arg->get_shape());
        }
        op->assert_shape(shapes);
        shape = op->get_out_shape(shapes);
        allocate();

        is_latent = true;
        is_constant = false;
        compute_value();
    }

    void node::compute_value()
    {
        if(is_latent)
        {
            std::vector<std::vector<double>>op_arg_val;
            for(std::shared_ptr<node> arg: op_args)
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

    void node::update_value(std::shared_ptr<node>a)
    {
        if(is_constant)
            throw IsConstant();
        if(is_latent)
            throw IsLatent();
        
        auto a_val = a->get_value();
        if(a_val.size() != value.size())
            throw SizeMismatch();
        value = a_val;
    }
    
    void node::forward_diff(std::vector<std::vector<double>>&Jzx, std::shared_ptr<node>&x)
    {
        int n = x->get_size();
        int m = size;
        Jzx = std::vector<std::vector<double>>(m, std::vector<double>(n, 0.0)); // Jzx shape: (m, n)
        if(is_latent)
        {
            std::vector<std::vector<double>>op_arg_val;
            for(std::shared_ptr<node> arg: op_args)
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
    }

    std::shared_ptr<node> node::get_grad(std::shared_ptr<node>x)
    {
        if(is_constant)
            throw IsConstant();

        compute_value();

        if(x->is_constant)
            throw IsConstant();

        std::vector<int>new_shape = shape;
        std::vector<int>x_shape = x->get_shape();
        new_shape.insert(new_shape.end(), x_shape.begin(), x_shape.end());
        std::vector<std::vector<double>> J;

        forward_diff(J, x);

        std::vector<double>grad;
        for(int i=0; i<J.size(); ++i)
            grad.insert(grad.end(), J[i].begin(), J[i].end());

        return std::shared_ptr<node>(new node(true, new_shape, grad));
    }
}