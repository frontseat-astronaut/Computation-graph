#include <op_api.h>

namespace dio 
{
    std::map<std::string, operation*>op;

    Node add(Node a, Node b, std::string key)
    {
        if(op.find("add") == op.end())
            op["add"] = new _add;

        if(key == "")
            key = "add_" + a->get_key() + "_" + b->get_key();

        Node c = new dep_variable(std::vector<Node>{a, b}, op["add"], key);
        return c;
    }

    Node multiply(Node a, Node b, std::string key)
    {
        if(op.find("multiply") == op.end())
            op["multiply"] = new _multiply;

        if(key == "")
            key = "multiply_" + a->get_key() + "_" + b->get_key();

        Node c = new dep_variable(std::vector<Node>{a, b}, op["multiply"], key);
        return c;
    }

    Node divide(Node a, Node b, std::string key)
    {
        if(op.find("divide") == op.end())
            op["divide"] = new _divide;

        if(key == "")
            key = "divide" + a->get_key() + "_" + b->get_key();

        Node c = new dep_variable(std::vector<Node>{a, b}, op["divide"], key);
        return c;
    }

    Node reciprocal(Node a, std::string key)
    {
        return divide(new constant(1,""), a, key);
    }

    Node minus(Node a, std::string key)
    {
        if(op.find("minus") == op.end())
            op["minus"] = new _minus;

        if(key == "")
            key = "minus" + a->get_key();

        Node c = new dep_variable(std::vector<Node>{a}, op["minus"], key);
        return c;
    }
}