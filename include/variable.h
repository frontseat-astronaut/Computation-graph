#ifndef __VARIABLE_H_INCLUDED__   
#define __VARIABLE_H_INCLUDED__  

#include <string>
#include <vector>

#include "array.h"
#include "node.h"
#include "exceptions.h"

namespace dio
{
    class constant: public array, public node
    {
        public:
        template<typename T>
        constant(T x, std::string name="")
        {
            set_name(name);
            assign(x, 1);
        }

    };
}

#endif