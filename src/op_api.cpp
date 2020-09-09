#include <op_api.h>

namespace dio 
{
    std::map<std::string, std::shared_ptr<operation>>op;

    Node add(Node a, Node b, std::string key)
    {
        if(op.find("add") == op.end())
            op["add"] = std::shared_ptr<operation>(new _add);

        if(key == "")
            key = "add_" + a->get_key() + "_" + b->get_key();

        Node c = Node(new dep_variable(std::vector<Node>{a, b}, op["add"], key));
        return c;
    }

    Node multiply(Node a, Node b, std::string key)
    {
        if(op.find("multiply") == op.end())
            op["multiply"] = std::shared_ptr<operation>(new _multiply);

        if(key == "")
            key = "multiply_" + a->get_key() + "_" + b->get_key();

        Node c = Node(new dep_variable(std::vector<Node>{a, b}, op["multiply"], key));
        return c;
    }

    Node divide(Node a, Node b, std::string key)
    {
        if(op.find("divide") == op.end())
            op["divide"] = std::shared_ptr<operation>(new _divide);

        if(key == "")
            key = "divide_" + a->get_key() + "_" + b->get_key();

        Node c = Node(new dep_variable(std::vector<Node>{a, b}, op["divide"], key));
        return c;
    }

    Node reciprocal(Node a, std::string key)
    {
        return divide(Node(new constant(1)), a, key);
    }

    Node minus(Node a, std::string key)
    {
        if(op.find("minus") == op.end())
            op["minus"] = std::shared_ptr<operation>(new _minus);

        if(key == "")
            key = "minus_" + a->get_key();

        Node c = Node(new dep_variable(std::vector<Node>{a}, op["minus"], key));
        return c;
    }

    Node powr(Node a, Node b, std::string key)
    {
        if(op.find("powr") == op.end())
            op["powr"] = std::shared_ptr<operation>(new _power);

        if(key == "")
            key = "power_" + a->get_key() + "_" + b->get_key();

        Node c = Node(new dep_variable(std::vector<Node>{a, b}, op["powr"], key));
        return c;
    }

    Node exp(Node a, std::string key)
    {
        return powr(Node(new constant(std::exp(1), key = "e")), a, key); 
    }
}