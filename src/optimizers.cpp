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

    void optimizer::get_grads(std::shared_ptr<node>f, std::map<std::shared_ptr<node>,std::vector<double>>&grads)
    {
        if(f->get_size() != 1)
            throw NotRealFunction();

        std::map<std::shared_ptr<node>, std::vector<std::vector<double>>>Jcache;
        f->reverse_diff(Jcache);

        for(auto param: parameters)
        {
            auto it = Jcache.find(param);
            if(it != Jcache.end())
                grads[param] = (*it).second[0];
        }
    }

    void optimizer::step(std::shared_ptr<node>f)
    {
        if(f->get_size() != 1)
            throw NotRealFunction();

        std::map<std::shared_ptr<node>,std::vector<double>>grads;
        get_grads(f, grads);

        update_parameters(grads);
    }

    // SGD 
    void SGD::update_parameters(std::map<std::shared_ptr<node>,std::vector<double>>&grads)
    {
        for(auto &item: grads)
        {
            std::shared_ptr<node>param = item.first;
            std::vector<double>value = param->get_value();
            std::vector<double>grad = item.second;
            scale_vector(grad, -learning_rate);
            add_vectors(value, value, grad);
            param->_update_value(value);
        }
    }
}