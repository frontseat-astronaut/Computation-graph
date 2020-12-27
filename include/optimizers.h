#ifndef __OPTIMIZERS_H_INCLUDED__   
#define __OPTIMIZERS_H_INCLUDED__  

#include <set>
#include <vector>
#include <memory>

#include "node.h"
#include "exceptions.h"

namespace dio
{
    class optimizer 
    {
        protected:
            std::vector<std::shared_ptr<node>>parameters;
            double learning_rate;

            void get_grads(std::shared_ptr<node>, std::map<std::shared_ptr<node>,std::vector<double>>&);
            void virtual update_parameters(std::map<std::shared_ptr<node>,std::vector<double>>&grads)=0;

        public: 
            void step(std::shared_ptr<node>);
            double get_lr();
            void virtual update_lr();
    };

    class SGD: public optimizer
    {
        public:
            void update_parameters(std::map<std::shared_ptr<node>,std::vector<double>>&grads);
    };
}

#endif