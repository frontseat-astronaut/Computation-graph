#ifndef __NODE_H_INCLUDED__   
#define __NODE_H_INCLUDED__  

#include <memory>
#include <vector>
#include <assert.h>

#include "exceptions.h"
#include "initializers.h"
#include "util.h"
#include "node_op.h"

namespace dio
{
    class node
    {
        protected:
            std::vector<double>value;
            std::vector<int>shape;
            int size = 0;
            bool is_allocated = 0;

            template<typename T>
            void set_value(int &idx, std::vector<T>&a)
            {
                for(int i=0; i<a.size(); ++i)
                    set_value(idx, a[i]);
            }
            void set_value(int &idx, double &x)
            {
                value[idx++] = x;
            }
            template<typename T>
            void set_value(T&a)
            {
                int idx = 0;
                set_value(idx, a);
            }
            void allocate(double x=0);
            void initialize(std::string&, std::vector<double>&);

            std::vector<std::shared_ptr<node>>op_args;
            std::shared_ptr<node_op>op;
            bool is_latent;
            bool is_constant;

        public:
            node(bool is_constant, std::vector<int>shape, double);
            node(std::vector<int>shape, std::string initializer, 
                 std::vector<double>init_args=std::vector<double>{});
            template<typename T>
            node(bool is_constant, T a)
            {
                shape = dio::get_shape(a);
                allocate();
                set_value(a);

                this->is_constant = is_constant;
                is_latent = false;
            }
            node(std::vector<std::shared_ptr<node>>op_args, std::shared_ptr<node_op>op);
            node(bool is_constant, std::vector<int>shape, std::vector<double>&a);

            std::vector<int> get_shape();
            int get_size();
            double get_idx_value(std::vector<int>vidx);

            void compute_value();
            void update_value(std::shared_ptr<node>);
            std::vector<double> get_value();

            void forward_diff(std::vector<std::vector<double>>&, std::shared_ptr<node>&);
            std::shared_ptr<node> virtual get_grad(std::shared_ptr<node>);

            void print();
            void print(int&, int, std::string&);

            void _change_shape(std::vector<int>&new_shape);
    };
}

#endif