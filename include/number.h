#ifndef __NUMBER_H_INCLUDED__   
#define __NUMBER_H_INCLUDED__  

#include<string>
#include<iostream>
#include<memory>

namespace dio 
{
    class number
    {
        protected:
            double value = 0;

        public:

            virtual double get_value()
            {
                return value;
            }

            virtual double get_gradient(std::shared_ptr<number>) = 0;

            virtual void set_value(double) {}
    };
}

#endif