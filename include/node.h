#ifndef __NODE_H_INCLUDED__   
#define __NODE_H_INCLUDED__  

#include<string>

namespace dio 
{
    class node
    {
        protected:
            std::string key;
            double value = 0;

        public:
            node(std::string key): key{key} {}
            node(double value, std::string key): value{value}, key{key} {}

            std::string get_key()
            {
                return key;
            }

            virtual double get_value()
            {
                return value;
            }

            virtual double get_gradient(std::string x_key) = 0;

            virtual void set_value(double) {}
    };
}

#endif