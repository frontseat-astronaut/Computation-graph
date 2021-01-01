#ifndef __CHECKS_H_INCLUDED__   
#define __CHECKS_H_INCLUDED__  

#include <assert.h>

#include "node.h"

namespace dio
{
    void gradient_check(std::shared_ptr<node>f, std::vector<std::vector<double>>grads, std::vector<std::shared_ptr<node>>parameters,
                        double EPSILON=1e-6);
}

#endif