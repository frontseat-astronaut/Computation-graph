#include <op_api.h>

namespace dio 
{
    Node Node::operator+(Node other)
    {
        auto op = std::shared_ptr<array_op>(new element_wise_op(std::shared_ptr<number_op>(new _add)));
        Node c = Node(new variable(std::vector<std::shared_ptr<array>>{arr_ptr,other.get()}, op));
        return c;
    }

    Node Node::operator*(Node other)
    {
        auto op = std::shared_ptr<array_op>(new element_wise_op(std::shared_ptr<number_op>(new _multiply)));
        Node c = Node(new variable(std::vector<std::shared_ptr<array>>{arr_ptr,other.get()}, op));
        return c;
    }

    Node Node::operator/(Node other)
    {
        auto op = std::shared_ptr<array_op>(new element_wise_op(std::shared_ptr<number_op>(new _divide)));
        Node c = Node(new variable(std::vector<std::shared_ptr<array>>{arr_ptr,other.get()}, op));
        return c;
    }

    Node Node::operator-(Node other)
    {
        auto op = std::shared_ptr<array_op>(new element_wise_op(std::shared_ptr<number_op>(new _add)));
        Node c = Node(new variable(std::vector<std::shared_ptr<array>>{arr_ptr, (-other).get()}, op));
        return c;
    }

    Node Node::operator-()
    {
        auto op = std::shared_ptr<array_op>(new element_wise_op(std::shared_ptr<number_op>(new _minus)));
        Node c = Node(new variable(std::vector<std::shared_ptr<array>>{arr_ptr}, op));
        return c;
    }
    
    Node Node::operator^(Node other)
    {
        auto op = std::shared_ptr<array_op>(new element_wise_op(std::shared_ptr<number_op>(new _powr)));
        Node c = Node(new variable(std::vector<std::shared_ptr<array>>{arr_ptr, other.get()}, op));
        return c;
    }

    Node exp(Node a)
    {
        return Node(new constant(a.get()->get_shape(), std::exp(1.0)))^a;
    }

    Node matmul(Node a, Node b)
    {
        return Node(new variable(std::vector<std::shared_ptr<array>>{a.get(), b.get()}, std::shared_ptr<array_op>(new _matmul)));
    }

    void get_indices(std::vector<std::vector<int>>&idx) {}

    Node ret_index(Node a, std::vector<std::vector<int>>&idx)
    {
        return Node(new variable(std::vector<std::shared_ptr<array>>{a.get()}, std::shared_ptr<array_op>(new _index(idx))));
    }

    Node concat(Node a, Node b, int axis)
    {
        axis = (axis+a.get()->get_size())%(a.get()->get_size());
        return Node(new variable(std::vector<std::shared_ptr<array>>{a.get(), b.get()}, std::shared_ptr<array_op>(new _concat(axis))));
    }
}