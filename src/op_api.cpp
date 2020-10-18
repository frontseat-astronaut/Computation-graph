#include <op_api.h>

namespace dio 
{
    // add
    Node Node::operator+(Node other)
    {
        auto op = std::shared_ptr<array_op>(new element_wise_op(std::shared_ptr<number_op>(new _add)));
        Node c = Node(new variable(std::vector<std::shared_ptr<array>>{arr_ptr,other.get()}, op));
        return c;
    }

    Node operator+(double a, Node b)
    {
        Node a_node = Node(new constant(b.get()->get_shape(), a));
        return a_node + b;
    }

    Node operator+(Node a, double b)
    {
        return b+a;
    }

    // multiply
    Node Node::operator*(Node other)
    {
        auto op = std::shared_ptr<array_op>(new element_wise_op(std::shared_ptr<number_op>(new _multiply)));
        Node c = Node(new variable(std::vector<std::shared_ptr<array>>{arr_ptr,other.get()}, op));
        return c;
    }

    Node operator*(double a, Node b)
    {
        Node a_node = Node(new constant(b.get()->get_shape(), a));
        return a_node * b;
    }

    Node operator*(Node a, double b)
    {
        return b*a;
    }

    // divide
    Node Node::operator/(Node other)
    {
        auto op = std::shared_ptr<array_op>(new element_wise_op(std::shared_ptr<number_op>(new _divide)));
        Node c = Node(new variable(std::vector<std::shared_ptr<array>>{arr_ptr,other.get()}, op));
        return c;
    }

    Node operator/(double a, Node b)
    {
        Node a_node = Node(new constant(b.get()->get_shape(), a));
        return a_node / b;
    }

    Node operator/(Node a, double b)
    {
        Node b_node = Node(new constant(a.get()->get_shape(), b));
        return a / b_node;
    }

    // subtract
    Node Node::operator-(Node other)
    {
        auto op = std::shared_ptr<array_op>(new element_wise_op(std::shared_ptr<number_op>(new _add)));
        Node c = Node(new variable(std::vector<std::shared_ptr<array>>{arr_ptr, (-other).get()}, op));
        return c;
    }

    Node operator-(double a, Node b)
    {
        Node a_node = Node(new constant(b.get()->get_shape(), a));
        return a_node - b;
    }

    Node operator-(Node a, double b)
    {
        Node b_node = Node(new constant(a.get()->get_shape(), b));
        return a - b_node;
    }

    // unary minus
    Node Node::operator-()
    {
        auto op = std::shared_ptr<array_op>(new element_wise_op(std::shared_ptr<number_op>(new _minus)));
        return Node(new variable(std::vector<std::shared_ptr<array>>{arr_ptr}, op));
    }

    // powr
    Node Node::operator^(Node other)
    {
        auto op = std::shared_ptr<array_op>(new element_wise_op(std::shared_ptr<number_op>(new _powr)));
        Node c = Node(new variable(std::vector<std::shared_ptr<array>>{arr_ptr, other.get()}, op));
        return c;
    }

    Node operator^(double a, Node b)
    {
        Node a_node = Node(new constant(b.get()->get_shape(), a));
        return a_node ^ b;
    }

    Node operator^(Node a, double b)
    {
        Node b_node = Node(new constant(a.get()->get_shape(), b));
        return a ^ b_node;
    }

    // e^x
    Node exp(Node a)
    {
        return Node(new constant(a.get()->get_shape(), std::exp(1.0)))^a;
    }

    // matrix multiplication
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