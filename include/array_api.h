#ifndef __ARRAYAPI_H_INCLUDED__   
#define __ARRAYAPI_H_INCLUDED__  

#include <memory>

#include "array.h"

namespace dio
{
    using Array = std::shared_ptr<array>;
}

#endif