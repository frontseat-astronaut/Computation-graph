#include <op_api.h>

namespace dio 
{
    // add
    Node Node::operator+(Node other)
    {
        auto op = std::shared_ptr<node_op>(new element_wise_op(std::shared_ptr<number_op>(new _add)));
        Node c = Node(new node(std::vector<std::shared_ptr<node>>{node_ptr,other.get()}, op));
        return c;
    }

    Node operator+(double a, Node b)
    {
        Node a_node = Node(new node(true, b.get()->get_shape(), a));
        return a_node + b;
    }

    Node operator+(Node a, double b)
    {
        return b+a;
    }

    // multiply
    Node Node::operator*(Node other)
    {
        auto op = std::shared_ptr<node_op>(new element_wise_op(std::shared_ptr<number_op>(new _multiply)));
        Node c = Node(new node(std::vector<std::shared_ptr<node>>{node_ptr,other.get()}, op));
        return c;
    }

    Node operator*(double a, Node b)
    {
        Node a_node = Node(new node(true, b.get()->get_shape(), a));
        return b * a_node;
    }

    Node operator*(Node a, double b)
    {
        return b*a;
    }

    // divide
    Node Node::operator/(Node other)
    {
        auto op = std::shared_ptr<node_op>(new element_wise_op(std::shared_ptr<number_op>(new _divide)));
        Node c = Node(new node(std::vector<std::shared_ptr<node>>{node_ptr,other.get()}, op));
        return c;
    }

    Node operator/(double a, Node b)
    {
        Node a_node = Node(new node(true, b.get()->get_shape(), a));
        return a_node / b;
    }

    Node operator/(Node a, double b)
    {
        Node b_node = Node(new node(true, a.get()->get_shape(), b));
        return a / b_node;
    }

    // subtract
    Node Node::operator-(Node other)
    {
        auto op = std::shared_ptr<node_op>(new element_wise_op(std::shared_ptr<number_op>(new _add)));
        Node c = Node(new node(std::vector<std::shared_ptr<node>>{node_ptr, (-other).get()}, op));
        return c;
    }

    Node operator-(double a, Node b)
    {
        Node a_node = Node(new node(true, b.get()->get_shape(), a));
        return a_node - b;
    }

    Node operator-(Node a, double b)
    {
        Node b_node = Node(new node(true, a.get()->get_shape(), b));
        return a - b_node;
    }

    // unary minus
    Node Node::operator-()
    {
        auto op = std::shared_ptr<node_op>(new element_wise_op(std::shared_ptr<number_op>(new _minus)));
        return Node(new node(std::vector<std::shared_ptr<node>>{node_ptr}, op));
    }

    // powr
    Node Node::operator^(Node other)
    {
        auto op = std::shared_ptr<node_op>(new element_wise_op(std::shared_ptr<number_op>(new _powr)));
        Node c = Node(new node(std::vector<std::shared_ptr<node>>{node_ptr, other.get()}, op));
        return c;
    }

    Node operator^(double a, Node b)
    {
        Node a_node = Node(new node(true, b.get()->get_shape(), a));
        return a_node ^ b;
    }

    Node operator^(Node a, double b)
    {
        Node b_node = Node(new node(true, a.get()->get_shape(), b));
        return a ^ b_node;
    }

    // e^x
    Node exp(Node a)
    {
        return Node(new node(true, a.get()->get_shape(), std::exp(1.0)))^a;
    }

    // log 
    Node log(Node a)
    {
        auto op = std::shared_ptr<node_op>(new element_wise_op(std::shared_ptr<number_op>(new _log)));
        return Node(new node(std::vector<std::shared_ptr<node>>{a.get()}, op));
    }

    // sigmoid 
    Node sigmoid(Node a)
    {
        auto op = std::shared_ptr<node_op>(new element_wise_op(std::shared_ptr<number_op>(new _sigmoid)));
        return Node(new node(std::vector<std::shared_ptr<node>>{a.get()}, op));
    }

    // relu 
    Node relu(Node a)
    {
        auto op = std::shared_ptr<node_op>(new element_wise_op(std::shared_ptr<number_op>(new _relu)));
        return Node(new node(std::vector<std::shared_ptr<node>>{a.get()}, op));
    }

    // matrix multiplication
    Node matmul(Node a, Node b)
    {
        return Node(new node(std::vector<std::shared_ptr<node>>{a.get(), b.get()}, std::shared_ptr<node_op>(new _matmul)));
    }

    // indexing
    Node Node::ret_index(std::vector<bool>&int_idx, std::vector<std::vector<int>>&idx)
    {
        Node c = Node(new node(std::vector<std::shared_ptr<node>>{node_ptr}, std::shared_ptr<node_op>(new _index(int_idx, idx))));
        return c;
    }

    // concat
    Node concat(Node a, Node b, int axis)
    {
        // axis = (axis+a.get()->get_size())%(a.get()->get_size());
        return Node(new node(std::vector<std::shared_ptr<node>>{a.get(), b.get()}, std::shared_ptr<node_op>(new _concat(axis))));
    }

    // reshape
    Node reshape(Node a, std::vector<int>shape)
    {
        return Node(new node(std::vector<std::shared_ptr<node>>{a.get()}, std::shared_ptr<node_op>(new _reshape(shape))));
    }

    // in-place reshape
    Node Node::reshape(std::vector<int>new_shape)
    {
        node_ptr->_change_shape(new_shape);
        return *this;
    } 

    // reduce sum 
    Node reduce_sum(Node a, std::vector<int>axes)
    {
        std::shared_ptr<number_op>op(new _add);
        return Node(new node(std::vector<std::shared_ptr<node>>{a.get()}, std::shared_ptr<node_op>(new _reduce_op(op, axes))));
    }

    // convolve 2D
    Node convolve_2D(Node x, Node kernel, std::vector<int>pad, std::vector<int>stride)
    {
        return Node(new node(std::vector<std::shared_ptr<node>>{x.get(), kernel.get()}, std::shared_ptr<node_op>(new _convolve_2D(pad, stride))));
    }

}