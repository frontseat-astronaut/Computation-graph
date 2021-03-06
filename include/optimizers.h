#ifndef __OPTIMIZERS_H_INCLUDED__   
#define __OPTIMIZERS_H_INCLUDED__  

#include <set>
#include <vector>
#include <memory>

#include "node.h"
#include "checks.h"
#include "exceptions.h"

namespace dio
{
    class optimizer 
    {
        protected:
            std::vector<std::shared_ptr<node>>parameters;
            double learning_rate;

            std::vector<std::vector<double>> get_grads(std::shared_ptr<node>f);
            void virtual update_parameters(std::vector<std::vector<double>>&grads)=0;

        public: 
            optimizer(std::vector<std::shared_ptr<node>>p, double lr): parameters{p}, learning_rate{lr} {}

            void step(std::shared_ptr<node>, bool do_gradient_check, double EPSILON);
            double get_lr();
            void virtual update_lr();
    };

    class sgd: public optimizer
    {
        private: 
            double momentum = 0;
            std::vector<std::vector<double>>velocity;

        public:
            sgd(std::vector<std::shared_ptr<node>>parameters, double learning_rate, double momentum);
            void update_parameters(std::vector<std::vector<double>>&grads);
    };

}

#endif