#include <checks.h>

namespace dio
{
    void gradient_check(std::shared_ptr<node>f, std::vector<std::vector<double>>grads, std::vector<std::shared_ptr<node>>parameters,
                        double EPSILON)
    {
        assert(parameters.size() == grads.size());
        // f->compute_value();
        // auto init_val = *(f->get_value());
        for(int i=0; i<parameters.size(); ++i)
        {
            auto param = parameters[i];
            std::vector<double> &value = *(param->get_value());
            std::vector<double> copy(value);
            std::vector<double> grad = grads[i];
            for(int j=0; j<value.size(); ++j)
            {
                value[j] = copy[j] + EPSILON; 
                f->compute_value();
                double fplus = (*(f->get_value()))[0];

                value[j] = copy[j] - EPSILON; 
                f->compute_value();
                double fminus = (*(f->get_value()))[0];

                value[j] = copy[j];

                double approx_grad = (fplus - fminus)/(2 * EPSILON);
                if(isnan(approx_grad))
                    continue;
                if(!iszero(grad[j]-approx_grad, 10*EPSILON))
                    throw GradientCheckFailure(approx_grad, grad[j], fplus, fminus, EPSILON);
            }
        }
        f->compute_value();
        // auto final_val = *(f->get_value());
        printf("\n[GRADIENT CHECK SUCCESSFUL]\n");
    }
}