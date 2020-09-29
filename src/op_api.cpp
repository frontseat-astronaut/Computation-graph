#include <op_api.h>

namespace dio 
{
    std::map<std::string, std::shared_ptr<array_op>>op;

    Node add(Node a, Node b)
    {
        if(op.find("add") == op.end())
            op["add"] = std::shared_ptr<array_op>(new element_wise_op(std::shared_ptr<number_op>(new _add)));

        Node c = Node(new variable(std::vector<Node>{a, b}, op["add"]));
        return c;
    }

    Node multiply(Node a, Node b)
    {
        if(op.find("multiply") == op.end())
            op["multiply"] = std::shared_ptr<array_op>(new element_wise_op(std::shared_ptr<number_op>(new _multiply)));

        Node c = Node(new variable(std::vector<Node>{a, b}, op["multiply"]));
        return c;
    }

    Node divide(Node a, Node b)
    {
        if(op.find("divide") == op.end())
            op["divide"] = std::shared_ptr<array_op>(new element_wise_op(std::shared_ptr<number_op>(new _divide)));

        Node c = Node(new variable(std::vector<Node>{a, b}, op["divide"]));
        return c;
    }

    Node reciprocal(Node a)
    {
        return divide(Node(new constant(a->get_shape(), 1.0)), a);
    }

    Node minus(Node a)
    {
        if(op.find("minus") == op.end())
            op["minus"] = std::shared_ptr<array_op>(new element_wise_op(std::shared_ptr<number_op>(new _minus)));

        Node c = Node(new variable(std::vector<Node>{a}, op["minus"]));
        return c;
    }

    Node powr(Node a, Node b)
    {
        if(op.find("powr") == op.end())
            op["powr"] = std::shared_ptr<array_op>(new element_wise_op(std::shared_ptr<number_op>(new _powr)));

        Node c = Node(new variable(std::vector<Node>{a, b}, op["powr"]));
        return c;
    }

    Node exp(Node a)
    {
        return powr(Node(new constant(a->get_shape(), std::exp(1.0))), a); 
    }

}