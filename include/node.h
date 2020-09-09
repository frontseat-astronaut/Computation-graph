#ifndef __NODE_H_INCLUDED__   
#define __NODE_H_INCLUDED__  

#include <string>

namespace dio
{
    namespace hidden 
    {
        class node 
        {
            protected:
                std::string key;
                node(std::string key): key(key) {} // can't create an instance of node

            public:
                std::string get_key()
                {
                    return key;
                }
        };
    }
}