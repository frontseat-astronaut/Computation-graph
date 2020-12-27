#include <node_api.h>

namespace dio
{
    Node Node::get_jacobian(Node b)
    {
        auto b_ptr = b.get();
        return Node(node_ptr->get_jacobian(b_ptr));
    }

    void Node::update_val(Node a)
    {
        a.compute_val();
        node_ptr->update_value(a.get());
    }

    void Node::compute_val()
    {
        node_ptr->compute_value();
    }

    void Node::print_val()
    {
        node_ptr->print();
    }

    double Node::val_at_index(std::vector<int>index)
    {
        return node_ptr->get_idx_value(index);
    }

    Node Variable(std::vector<int>shape, std::string initializer, 
        std::vector<double>init_args)
    {
        return Node(new node(shape, initializer, init_args));
    }
}