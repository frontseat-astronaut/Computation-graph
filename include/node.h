#ifndef __NODE_H_INCLUDED__   
#define __NODE_H_INCLUDED__  

#include <string>

namespace dio
{
    class node
    {
        protected:
            std::string name;
            node() {}
        
        public:
            void set_name(std::string x)
            {
                name = x;
            }
    };
}

#endif