#ifndef __FUNCTOR_H_INCLUDED__   
#define __FUNCTOR_H_INCLUDED__  

#include <map>
#include <memory>
#include <string>

#include "op_api.h"
#include "node_api.h"
#include "exceptions.h"

namespace dio
{
    class Functor
    {
        private: 
            // OPTIONAL: can be provided via functor::set_input_shape()
            bool input_shape_set = false;
            std::vector<int>input_shape;

            // OPTIONAL: Will store pointers to all NON-LATENT variables used in forward pass, iff functor::store_parameters=true
            bool found_parameters = false;
            std::vector<Node> parameters;

        protected:
            void set_input_shape(std::vector<int>input_shape);

            bool store_parameters=true;
            bool find_parameters_every_call=false;
            void find_parameters();
            void find_parameters(Node input);

            // User should either set fixed input_shape using set_input_shape(), or implement own assert_input_shape() 
            virtual void assert_input_shape(std::vector<int>input_shape);
            virtual Node call(Node input)=0;

        public:
            Node operator()(Node input);
            std::vector<Node> get_parameters();
    };

    class Linear: public Functor 
    {
        protected:
            int input_dim;
            int output_dim;
            bool use_bias;
            std::string activation_function;

            Node W, b;
            Node call(Node input);

        public: 
            Linear(int input_dim, int output_dim, std::string activation_function="", std::string initializer="zeros", bool use_bias=true);
    };
}

#endif