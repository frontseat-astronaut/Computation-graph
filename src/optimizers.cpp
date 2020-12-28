#include <optimizers.h>

namespace dio 
{
    // optimizer
    double optimizer::get_lr()
    {
        return learning_rate;
    }

    void optimizer::update_lr()
    {
        return;
    }

    std::vector<std::vector<double>> optimizer::get_grads(std::shared_ptr<node>f)
    {
        if(f->get_size() != 1)
            throw NotRealFunction();

        std::map<long long, std::vector<std::vector<double>>>Jcache = f->reverse_diff();

        std::vector<std::vector<double>>grads(parameters.size());
        for(int i=0; i<parameters.size(); ++i)
        {
            auto param = parameters[i];
            long long key = (long long)param.get();
            if(Jcache.find(key) == Jcache.end())
                grads[i] = std::vector<double>(param->get_size());
            else
                grads[i] = Jcache[key][0];
        }
        return grads;
    }

    void optimizer::step(std::shared_ptr<node>f)
    {
        if(f->get_size() != 1)
            throw NotRealFunction();

        auto grads = get_grads(f);

        // printf("\n[COMPUTED GRADIENTS]\n");
        // fflush(stdout);

        update_parameters(grads);
    }

    // sgd 
    sgd::sgd(std::vector<std::shared_ptr<node>>parameters, double learning_rate): optimizer(parameters, learning_rate) {}

    void sgd::update_parameters(std::vector<std::vector<double>>&grads)
    {
        for(int i=0; i<parameters.size(); ++i)
        {
            std::shared_ptr<node> param = parameters[i];
            std::vector<double> &value = *(param->get_value());
            std::vector<double> grad = grads[i];
            scale_vector(grad, -learning_rate);
            add_vectors(value, value, grad);
        }
    }
}