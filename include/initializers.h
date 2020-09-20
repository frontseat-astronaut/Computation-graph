#ifndef __INITIALIZERS_H_INCLUDED__   
#define __INITIALIZERS_H_INCLUDED__  

#include <random>

namespace dio
{
    class initializer
    {
        public:
            void virtual initialize(double &)=0;
    };

    class ZerosInitializer: public initializer 
    {
        public:
            void initialize(double &x)
            {
                x = 0;
            }
    };

    class GaussianInitializer: public initializer 
    {
        private:
            double mean, variance;
            std::default_random_engine generator;
            std::normal_distribution<double> distribution;

        public:
            GaussianInitializer(double mean, double variance): 
                mean{mean}, variance{variance}
            {
                distribution = std::normal_distribution<double>(mean, variance);
            }

            void initialize(double &x)
            {
                x = distribution(generator);
            }
    };
}

#endif