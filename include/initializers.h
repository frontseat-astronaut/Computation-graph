#ifndef __INITIALIZERS_H_INCLUDED__   
#define __INITIALIZERS_H_INCLUDED__  

#include <random>
#include <cmath>

namespace dio
{
    class initializer
    {
        public:
            void virtual initialize(std::vector<std::shared_ptr<number>>&)=0;
    };

    class ZerosInitializer: public initializer 
    {
        public:
            void initialize(std::vector<std::shared_ptr<number>>&a)
            {
                for(int i=0; i<a.size(); ++i)
                    a[i]->set_value(0);
            }
    };

    class GaussianInitializer: public initializer 
    {
        private:
            double mean, variance;

        public:
            GaussianInitializer(double mean, double variance): 
                mean{mean}, variance{sqrt(variance)} {}

            void initialize(std::vector<std::shared_ptr<number>>&a)
            {
                std::random_device rd{};
                std::mt19937 gen{rd()};
                std::normal_distribution <double> d{mean, variance};
                for(int i=0; i<a.size(); ++i)
                    a[i]->set_value(d(gen));
            }
    };
}

#endif